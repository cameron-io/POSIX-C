#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-Type: text/plain\r\n\r\n";

int main() {
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(
        bind_address->ai_family,
        bind_address->ai_socktype,
        bind_address->ai_protocol
    );
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    
    printf("Binding socket to local address...\n");
    int err = bind(
        socket_listen,
        bind_address->ai_addr,
        bind_address->ai_addrlen
    );
    if (err) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    
    freeaddrinfo(bind_address);

    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    printf("Listening on http://localhost:%d\n", 8080);

    printf("Waiting for connections...\n");

    while(1) {
        struct sockaddr* client_sa = NULL;
        socklen_t client_sa_len = sizeof(client_sa);
        
        SOCKET socket_client = accept(socket_listen, client_sa, &client_sa_len);

        if (!ISVALIDSOCKET(socket_client)) {
            fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
            exit(1);
        }

        printf("Client is connected...\n");
        
        char client_addr[NI_MAXHOST] = "";
        int error = getnameinfo(
            client_sa, client_sa_len, client_addr, sizeof(client_addr), NULL, 0, NI_NUMERICHOST);

        char request[1024];
        int bytes_recv = recv(socket_client, request, 1024, 0);
        printf("Connected to: %s (err: %d)\n", client_addr, error);
        printf("Received: %d bytes", bytes_recv);

        printf("Sending response...\n");
        int bytes_sent = send(socket_client, response, strlen(response), 0);
        printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

        char *payload = request;
        bytes_sent = send(socket_client, payload, strlen(payload), 0);

        int payload_len = (int)strlen(payload);

        printf("Sent %d of %d bytes.\n", bytes_sent, payload_len);

        printf("Closing connection...\n");
        CLOSESOCKET(socket_client);
    }

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

    printf("Finished.\n");

    return 0;
}
