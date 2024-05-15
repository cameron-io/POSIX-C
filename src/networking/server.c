#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

SOCKET
socket_init(struct addrinfo *bind_address) {
    SOCKET new_socket;
    new_socket = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(new_socket)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    return new_socket;
}

void
socket_set_opt(SOCKET socket) {
    int option = 0;
    if (setsockopt(socket, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&option, sizeof(option))) {
        fprintf(stderr, "setsockopt() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
}

void
socket_bind(SOCKET socket, struct addrinfo *bind_address) {
    printf("Binding socket to local address...\n");
    if (bind(socket,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
}

void
socket_listen(SOCKET socket) {
    if (listen(socket, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
}

SOCKET
socket_await(SOCKET socket, struct sockaddr_storage client_address_store, socklen_t client_len) {
    SOCKET socket_client = accept(socket,
            (struct sockaddr*) &client_address_store, &client_len);
    if (!ISVALIDSOCKET(socket_client)) {
        fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    return socket_client;
}

void
socket_handle_client(struct sockaddr_storage client_address_store, socklen_t client_len) {
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_address_store,
            client_len, address_buffer, sizeof(address_buffer), 0, 0,
            NI_NUMERICHOST);
    printf("%s\n", address_buffer);
}

void
socket_read_client_request(SOCKET socket_client) {
    char request[1024];
    int bytes_received = recv(socket_client, request, 1024, 0);
    printf("Received %d bytes.\n", bytes_received);
    printf("%.*s \n", bytes_received, request);
}

int
socket_send_response(SOCKET socket_client) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local time is: ";
    int bytes_sent = send(socket_client, response, strlen(response), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));
    return bytes_sent;
}

char
*make_payload() {
    time_t timer;
    time(&timer);
    char *time_msg = ctime(&timer);
}

int
main() {
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    SOCKET socket = socket_init(bind_address);
    socket_set_opt(socket);
    socket_bind(socket, bind_address);
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    socket_listen(socket);

    while(1) {
        printf("Waiting for connection...\n");
        struct sockaddr_storage client_address_store;
        socklen_t client_len = sizeof(client_address_store);
        SOCKET socket_client = socket_await(socket, client_address_store, client_len);

        printf("Client is connected...\n");
        socket_handle_client(client_address_store, client_len);

        printf("Reading request...\n");
        socket_read_client_request(socket_client);

        printf("Sending response...\n");
        int bytes_sent = socket_send_response(socket_client);

        char *payload = make_payload();
        bytes_sent = send(socket_client, payload, strlen(payload), 0);

        int payload_len = (int)strlen(payload);

        while(bytes_sent < payload_len) {}

        printf("Sent %d of %d bytes.\n", bytes_sent, payload_len);

        printf("Closing connection...\n");
        CLOSESOCKET(socket_client);
    }

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket);

    printf("Finished.\n");

    return 0;
}
