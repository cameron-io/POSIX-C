#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>

int main() {
    struct ifaddrs* addr_node;
    
    if (getifaddrs(&addr_node) == -1) {
        printf("Could not get Interface Addresses");
        return -1;
    }
    printf("\033[1;36mName\tSA Family\tAddress Protocol\033[0m\n");
    while (addr_node) {
        if (!addr_node->ifa_addr) {
            addr_node = addr_node->ifa_next;
            continue;
        }
        int sock_addr_family = addr_node->ifa_addr->sa_family;
        if (sock_addr_family == AF_INET || sock_addr_family == AF_INET6) {
            printf("%s\t", addr_node->ifa_name);
            printf("%s\t", sock_addr_family == AF_INET ? "IPv4" : "IPv6");

            char addr_proto[100];
            const int sock_addr_family_size = sock_addr_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

            getnameinfo(addr_node->ifa_addr, sock_addr_family_size, addr_proto, sizeof(addr_proto), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", addr_proto);
        }
        addr_node = addr_node->ifa_next;
    }

    freeifaddrs(addr_node);
    return 0;
}
