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

#ifndef CDNS_CNAME_H
#define CDNS_CNAME_H

#include "resource_record.h"
#define TYPE_CNAME 5

/**
 * Represents a CNAME Record, which contains a canonical or primary name for the
 * owner.
 */
typedef struct {
  char name[255]; /**< The name that this record contains an answer for. */

  uint16_t type; /**< The type of this record. This should always be
                       TYPE_CNAME. */

  uint16_t class; /**< The class of this record. */

  uint16_t ttl; /**< The time-to-live of this record. */

  char cname[255]; /**< A domain name that specifies the canonical or primary
                        name for the owner. */
} DNSCNameRecord;

/**
 * Casts a DNSCNameRecord into a generic DNSResourceRecord for packing into a
 * message.
 *
 * @param resource_record The resource record to cast to.
 * @param cname The CNAME record to cast.
 */
void dns_cast_cname_to_resource(DNSResourceRecord *resource_record,
                                const DNSCNameRecord *cname);

/**
 * Casts a generic DNSResourceRecord into a DNSCNameRecord.
 *
 * @param cname The CNAME record to cast to.
 * @param resource_record The resource record to cast.
 */
void dns_cast_resource_to_cname(DNSCNameRecord *cname,
                                const DNSResourceRecord *resource_record,
                                const char *message_root);

#endif /* CDNS_CNAME_H */
