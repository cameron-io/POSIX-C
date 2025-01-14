#ifndef SERVER_H
#define SERVER_H

#include "netdb.h"
#include <unistd.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

SOCKET socket_init(struct addrinfo *bind_address);
void socket_set_opt(SOCKET socket);
void socket_set_opt(SOCKET socket);
void socket_bind(SOCKET socket, struct addrinfo *bind_address);
void socket_listen(SOCKET socket);
SOCKET socket_await(
    SOCKET socket,
    struct sockaddr_storage client_address_store,
    socklen_t client_len
);
void socket_handle_client(
    struct sockaddr_storage client_address_store,
    socklen_t client_len
);
void socket_read_client_request(SOCKET socket_client);
int socket_send_response(SOCKET socket_client);
char *make_payload();

#endif