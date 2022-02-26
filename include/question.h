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

#ifndef CDNS_QUESTION_H
#define CDNS_QUESTION_H

#include <stdint.h>
#include <stddef.h>

#define QTYPE_AXFR 252
#define QTYPE_MAILB 253
#define QTYPE_MAILA 254
#define QTYPE_ANY 255

#define CLASS_IN 1
#define CLASS_CS 2
#define CLASS_CH 3
#define CLASS_HS 4

#define QCLASS_ALL 255

/**
 * Represents a DNS question.
 */
typedef struct {
  char qname[64]; /**< The question's domain name. */

  uint16_t qtype; /**< The question's type. This can be any TYPE_ or QTYPE_
                       value. */

  uint16_t qclass; /**< The question's class. This can be any CLASS_ or
                        QCLASS_ value. */
} DNSQuestion;

/**
 * Packs a DNS question into bytes.
 *
 * @param bytes The byte array / memory to pack into.
 * @param question The DNS question to pack.
 * @return The number of bytes packed.
 */
size_t dns_question_pack(char *bytes, const DNSQuestion *question);

/**
 * Unpacks a DNS question from bytes.
 *
 * @param question The DNS question to unpack into.
 * @param bytes The byte array / memory to unpack.
 * @return The number of bytes unpacked.
 */
size_t dns_question_unpack(DNSQuestion *question, const char *bytes);

#endif /* CDNS_QUESTION_H */
