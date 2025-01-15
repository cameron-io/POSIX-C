#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H

#include "web_server/server.h"

SOCKET create_socket(const char* host, const char *port);

#endif