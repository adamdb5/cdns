/*
 * Copyright (c) 2022 Adam Bruce
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
    header->qr = (flags & (0x1 << 15)) >> 15;
    header->opcode = (flags & (0xF << 11)) >> 11;
    header->aa = (flags & (0x1 << 10)) >> 10;
    header->tc = (flags & (0x1 << 9)) >> 9;
    header->rd = (flags & (0x1 << 8)) >> 8;
    header->ra = (flags & (0x1 << 7)) >> 7;
    header->z = (flags & (0x7 << 4)) >> 4;
    header->rcode = flags & 0xF;
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
