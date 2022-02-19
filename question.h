//
// Created by adam on 18/02/2022.
//

#ifndef CDNS_QUESTION_H
#define CDNS_QUESTION_H

#include <stdint.h>

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

typedef struct {
    char qname[64];
    uint16_t qtype;
    uint16_t qclass;
} DNSQuestion;

size_t dns_question_unpack(DNSQuestion *question, const char *bytes);
size_t dns_question_pack(char *bytes, const DNSQuestion *question);

#endif //CDNS_QUESTION_H
