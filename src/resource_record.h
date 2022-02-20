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

#ifndef CDNS_RESOURCE_RECORD_H
#define CDNS_RESOURCE_RECORD_H

#include <stdint.h>
#include <stddef.h>

/**
 * Represents a generic DNS resource record. These can be cast into a record
 * type using the <code>dns_cast_</code> functions.
 */
typedef struct {
    char name[255];    /**< The resource record's domain name. */

    uint16_t type;     /**< The type of this record. This can be any TYPE_
                            value. This value should be checked before
                            casting. */

    uint16_t class;    /**< The class of this record. This can be any CLASS_
                            value. */

    uint32_t ttl;      /**< The time-to-live of this record. */

    uint16_t rdlength; /**< The length of the data in this record. */

    char rdata[512];   /**< A byte array containing the data for this record. */
} DNSResourceRecord;

/**
 * Packs a DNS resource record into bytes. This does not use compression when
 * packing.
 *
 * @param bytes The byte array / memory to pack into.
 * @param record The DNS record to pack.
 * @return The number of bytes packed.
 */
size_t dns_resource_record_pack(char *bytes, const DNSResourceRecord *record);

/**
 * Unpacks a DNS resource record from bytes.
 *
 * @param record The DNS question to unpack into.
 * @param bytes The byte array / memory to unpack.
 * @param message_root A pointer to the start of the DNS message. This is
 *                     required for record decompression.
 * @return The number of bytes unpacked.
 */
size_t dns_resource_record_unpack(DNSResourceRecord *record,
                                  const char *bytes, const char *message_root);

#endif //CDNS_RESOURCE_RECORD_H
