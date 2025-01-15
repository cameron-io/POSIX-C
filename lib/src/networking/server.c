#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

SOCKET
socket_init(struct addrinfo *bind_address) {
    SOCKET new_socket;
    new_socket = socket(
        bind_address->ai_family,
        bind_address->ai_socktype,
        bind_address->ai_protocol
    );
    if (!ISVALIDSOCKET(new_socket)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }
    return new_socket;
}

void
socket_bind(SOCKET socket, struct addrinfo *bind_address) {
    printf("Binding socket to local address...\n");
    int err = bind(
        socket,
        bind_address->ai_addr,
        bind_address->ai_addrlen
    );
    if (err) {
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
socket_accept(
    SOCKET socket,
    struct sockaddr *sa,
    socklen_t sa_len
) {
    SOCKET socket_client = accept(socket, sa, &sa_len);

    if (!ISVALIDSOCKET(socket_client)) {
        fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
        exit(1);
    }

    return socket_client;
}

int
socket_get_info(struct sockaddr *sa, socklen_t sa_len) {
    char addr[NI_MAXHOST] = "";
    int error;

    error = getnameinfo(sa, sa_len, addr, sizeof(addr), NULL, 0, NI_NAMEREQD);

    if (error == 0) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_DGRAM; /*dummy*/
        hints.ai_flags = AI_NUMERICHOST;

        if	(getaddrinfo(addr, "0",	&hints,	&res) == 0) {
            /*	malicious PTR record */
            freeaddrinfo(res);
            printf("bogus PTR record\n");
            return -1;
        }
        /*	addr is	FQDN as	a result of PTR	lookup */
    } else {
        /*	addr is	numeric	string */
        error = getnameinfo(
            sa, sa_len, addr, sizeof(addr), NULL, 0, NI_NUMERICHOST);
        printf("\nErr: %d", error);
    }

    printf("\nConnected Address: %s\n", addr);

    return 0;
}

void
socket_read_client_request(SOCKET socket_client, char* request) {
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
