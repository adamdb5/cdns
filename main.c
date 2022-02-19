#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "header.h"
#include "question.h"
#include "message.h"

int dns_query(DNSMessage *response, const DNSMessage *message, const char *name_server) {
    int sock;
    struct sockaddr_in ns;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        return 1;
    }

    memset(&ns, 0, sizeof(struct sockaddr_in));
    ns.sin_family = AF_INET;
    ns.sin_addr.s_addr = inet_addr(name_server);
    ns.sin_port = htons(53);

    char buffer[512];
    memset(buffer, 0, 512);
    size_t len = dns_message_pack(buffer, message);

    ssize_t bytes_sent = sendto(sock, buffer, len, 0, (const struct sockaddr *) &ns, sizeof(ns));
    if(bytes_sent < 12) {
        close(sock);
        return 1;
    }

    memset(buffer, 0, 512);
    unsigned int from_len = sizeof(ns);
    ssize_t bytes_received = recvfrom(sock, buffer, 512, 0, (struct sockaddr *) &ns, &from_len);

    if(bytes_received < 12) {
        close(sock);
        return 1;
    }

    dns_message_unpack(response, buffer);

    return close(sock);
}

int main() {
    DNSMessage response;

    DNSMessage request = {
            .header = {
                    .id = 0xbeef,
                    .qdcount = 1,
                    .rd = 1
            },
            .question = {
                    .qname = "www.google.com",
                    .qclass = CLASS_IN,
                    .qtype = TYPE_HINFO
            }
    };

    dns_query(&response, &request, "8.8.8.8");

    return 0;
}
