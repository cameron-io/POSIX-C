#include <string.h>
#include <stdio.h>
#include "server.h"

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

    printf("Listening on http://localhost:%d\n", 8080);
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

        printf("Sent %d of %d bytes.\n", bytes_sent, payload_len);

        printf("Closing connection...\n");
        CLOSESOCKET(socket_client);
    }

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket);

    printf("Finished.\n");

    return 0;
}
