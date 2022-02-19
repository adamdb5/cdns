//
// Created by adam on 18/02/2022.
//

#ifndef CDNS_HEADER_H
#define CDNS_HEADER_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint16_t id;
    uint16_t qr;
    uint16_t opcode;
    uint16_t aa;
    uint16_t tc;
    uint16_t rd;
    uint16_t ra;
    uint16_t z;
    uint16_t rcode;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} DNSHeader;

uint16_t dns_header_flags_pack(const DNSHeader *header);
void dns_header_flags_unpack(DNSHeader *header, uint16_t flags);

size_t dns_header_unpack(DNSHeader *header, const char *bytes);
size_t dns_header_pack(char *bytes, const DNSHeader *header);

#endif //CDNS_HEADER_H
