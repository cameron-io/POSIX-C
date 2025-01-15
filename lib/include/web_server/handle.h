#ifndef WEB_HANDLE_H
#define WEB_HANDLE_H

#include "web_server/server.h"
#include "web_server/core.h"

void serve_resource(struct client_info **client_list,
        struct client_info *client, const char *path, const char* base_path);

#endif