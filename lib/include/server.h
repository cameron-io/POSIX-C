#ifndef SERVER_H
#define SERVER_H

#include "netdb.h"
#include <unistd.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

SOCKET socket_init(struct addrinfo *bind_address);
void socket_bind(SOCKET socket, struct addrinfo *bind_address);
void socket_listen(SOCKET socket);
SOCKET socket_accept(
    SOCKET socket,
    struct sockaddr *client_address_store,
    socklen_t client_len
);
int socket_get_info(struct sockaddr *sa, socklen_t sa_len);
void socket_read_client_request(SOCKET socket_client, char* request);
int socket_send_response(SOCKET socket_client);

#endif