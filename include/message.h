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

#ifndef CDNS_MESSAGE_H
#define CDNS_MESSAGE_H

#include "header.h"
#include "question.h"
#include "resource_record.h"

/**
 * Represents a DNS message.
 */
typedef struct {
  DNSHeader header; /**< The message's header. */

  DNSQuestion question; /**< The message's question. */

  DNSResourceRecord answers[10]; /**< The message's answers. Contains
                                      header.ancount answers. */

  DNSResourceRecord authority[10]; /**< The messages's authority records.
                                        Contains header.nscount records. */

  DNSResourceRecord additional[10]; /**< The messages's additional records.
                                         Contains header.arcount records. */

} DNSMessage;

/**
 * Packs a DNS message into bytes.
 *
 * @param bytes The byte array / memory to pack into.
 * @param message The DNS message to pack.
 * @return The number of bytes packed.
 */
size_t dns_message_pack(char *bytes, const DNSMessage *message);

/**
 * Unpacks a DNS message from bytes.
 *
 * @param message The DNS message to unpack into.
 * @param bytes The byte array / memory to unpack.
 * @return The number of bytes unpacked.
 */
size_t dns_message_unpack(DNSMessage *message, const char *bytes);

#endif /* CDNS_MESSAGE_H */
