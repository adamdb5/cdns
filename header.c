//
// Created by adam on 18/02/2022.
//

#include <netinet/in.h>
#include "header.h"

uint16_t dns_header_flags_pack(const DNSHeader *header) {
    uint16_t flags = 0;
    flags |= header->qr << 15;
    flags |= header->opcode << 11;
    flags |= header->aa << 10;
    flags |= header->tc << 9;
    flags |= header->rd << 8;
    flags |= header->ra << 7;
    flags |= header->z << 4;
    flags |= header->rcode;
    return flags;
}

void dns_header_flags_unpack(DNSHeader *header, uint16_t flags) {
    header->qr = (flags & (0b1 << 15)) >> 15;
    header->opcode = (flags & (0b1111 << 11)) >> 11;
    header->aa = (flags & (0b1 << 10)) >> 10;
    header->tc = (flags & (0b1 << 9)) >> 9;
    header->rd = (flags & (0b1 << 8)) >> 8;
    header->ra = (flags & (0b1 << 7)) >> 7;
    header->z = (flags & (0b111 << 4)) >> 4;
    header->rcode = flags & 0b1111;
}

size_t dns_header_unpack(DNSHeader *header, const char *bytes) {
    const uint16_t *short_iter = (uint16_t *) bytes;
    header->id = ntohs(short_iter[0]);
    dns_header_flags_unpack(header, ntohs(short_iter[1]));
    header->qdcount = ntohs(short_iter[2]);
    header->ancount = ntohs(short_iter[3]);
    header->nscount = ntohs(short_iter[4]);
    header->arcount = ntohs(short_iter[5]);
    return 12;
}

size_t dns_header_pack(char *bytes, const DNSHeader *header) {
    ((uint16_t *) bytes)[0] = htons(header->id);
    ((uint16_t *) bytes)[1] = htons(dns_header_flags_pack(header));
    ((uint16_t *) bytes)[2] = htons(header->qdcount);
    ((uint16_t *) bytes)[3] = htons(header->ancount);
    ((uint16_t *) bytes)[4] = htons(header->nscount);
    ((uint16_t *) bytes)[5] = htons(header->arcount);
    return 12;
}
