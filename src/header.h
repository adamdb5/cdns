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

#ifndef CDNS_HEADER_H
#define CDNS_HEADER_H

#include <stddef.h>
#include <stdint.h>

/**
 * Represents a DNS message header.
 */
typedef struct {
    uint16_t id;      /**< The ID of this message. */

    uint16_t qr;      /**< Whether this message is a query (0) or
                           a response (1). */

    uint16_t opcode;  /**< Specifies what kind of query this is. Possible values
                           are OPCODE_QUERY, OPCODE_IQUERY and OPCODE_STATUS. */

    uint16_t aa;      /**< Specifies whether the responding name server is an
                           authority for the given domain name. */

    uint16_t tc;      /**< Specifies whether this message was truncated. */

    uint16_t rd;      /**< Specifies whether recursion should be used. */

    uint16_t ra;      /**< Specifies whether recursion is supported by the name
                           server. */

    uint16_t z;       /**< Reserved. */

    uint16_t rcode;   /**< The response code. Possible values are RCODE_OK,
                           RCODE_FORMAT_ERROR, RCODE_SERVER_FAILURE,
                           RCODE_NAME_ERROR, RCODE_NOT_IMPLEMENTED and
                           RCODE_REFUSED. */

    uint16_t qdcount; /**< The number of questions in this message
                           (must be 1). */

    uint16_t ancount; /**< The number of answer records in this message. */

    uint16_t nscount; /**< The number of authority records in this message. */

    uint16_t arcount; /**< The number of additional records in this message. */
} DNSHeader;

/**
 * Packs DNS header flags into a 16-bit integer.
 *
 * @param header The DNS header containing the flags to pack.
 * @return The packed flags.
 */
uint16_t dns_header_flags_pack(const DNSHeader *header);

/**
 * Unpacks DNS header flags from a 16-bit integer.
 *
 * @param header The header to unpack the flags into.
 * @param flags The packed flags.
 */
void dns_header_flags_unpack(DNSHeader *header, uint16_t flags);

/**
 * Packs a DNS header into bytes.
 *
 * @param bytes The byte array / memory to pack into.
 * @param header The DNS header to pack.
 * @return The number of bytes packed.
 */
size_t dns_header_pack(char *bytes, const DNSHeader *header);

/**
 * Unpacks a DNS header from bytes.
 *
 * @param header The DNS header to unpack into.
 * @param bytes The byte array / memory to unpack.
 * @return The number of bytes unpacked.
 */
size_t dns_header_unpack(DNSHeader *header, const char *bytes);

#endif /* CDNS_HEADER_H */
