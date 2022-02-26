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

#ifndef CDNS_AAAA_H
#define CDNS_AAAA_H

#include "question.h"
#include "resource_record.h"
#include <netinet/in.h>
#include <string.h>

#define TYPE_AAAA 28
#define DNS_AAAA_RECORD_ADDRESS_LENGTH 16

/**
 * Represents an AAAA Record, which contains an IPv6 address.
 */
typedef struct {
  char name[255]; /**< The name that this record contains an answer for. */

  uint16_t type; /**< The type of this record. This should always be
                      TYPE_AAAA. */

  uint16_t class; /**< The class of this record. This should always be
                       CLASS_IN. */

  uint16_t ttl; /**< The time-to-live of this record. */

  uint8_t address[DNS_AAAA_RECORD_ADDRESS_LENGTH]; /**< The IPv6 address for
                                                        the given name. */
} DNSAAAARecord;

/**
 * Casts a DNSAAAARecord into a generic DNSResourceRecord for packing into a
 * message.
 *
 * @param resource_record The resource record to cast to.
 * @param aaaa The aaaa record to cast.
 */
void dns_cast_aaaa_to_resource(DNSResourceRecord *resource_record,
                               const DNSAAAARecord *aaaa);

/**
 * Casts a generic DNSResourceRecord into a DNSAAAARecord.
 *
 * @param aaaa The AAAA record to cast to.
 * @param resource_record The resource record to cast.
 */
void dns_cast_resource_to_aaaa(DNSAAAARecord *aaaa,
                               const DNSResourceRecord *resource_record);

#endif /* CDNS_AAAA_H */
