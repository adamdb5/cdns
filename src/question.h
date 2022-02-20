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

#define TYPE_A 1
#define TYPE_NS 2
#define TYPE_CNAME 5
#define TYPE_SOA 6
#define TYPE_PTR 12
#define TYPE_HINFO 13
#define TYPE_MX 15
#define TYPE_TXT 16
#define TYPE_RP 17
#define TYPE_AFSDB 18
#define TYPE_SIG 24
#define TYPE_KEY 25
#define TYPE_AAAA 28
#define TYPE_LOC 29
#define TYPE_SRV 33
#define TYPE_NAPTR 35
#define TYPE_KX 36
#define TYPE_CERT 37
#define TYPE_DNAME 38
#define TYPE_APL 42
#define TYPE_DS 43
#define TYPE_SSHFP 44
#define TYPE_IPSECKEY 45
#define TYPE_RRSIG 46
#define TYPE_NSEC 47
#define TYPE_DNSKEY 48
#define TYPE_DHCID 49
#define TYPE_NSEC3 50
#define TYPE_NSEC3PARAM 51
#define TYPE_TLSA 52
#define TYPE_SMIMEA 53
#define TYPE_HIP 55
#define TYPE_CDS 59
#define TYPE_CDNSKEY 60
#define TYPE_OPENGPGKEY 61
#define TYPE_CSYNC 62
#define TYPE_ZONEMD 63
#define TYPE_SVCB 64
#define TYPE_HTTPS 65
#define TYPE_EUI48 108
#define TYPE_EUI64 109
#define TYPE_TKEY 249
#define TYPE_TSIG 250
#define TYPE_URI 256
#define TYPE_CAA 257
#define TYPE_TA 32768
#define TYPE_DLV 32769

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
