//
// Created by adam on 19/02/2022.
//

#ifndef CDNS_RESOURCE_RECORD_H
#define CDNS_RESOURCE_RECORD_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char name[255];
    uint16_t type;
    uint16_t class;
    uint32_t ttl;
    uint16_t rdlength;
    char rdata[512];
} DNSResourceRecord;

size_t dns_resource_record_pack(char *bytes, const DNSResourceRecord *record);
size_t dns_resource_record_unpack(DNSResourceRecord *record, const char *bytes, const char *question_root);

#endif //CDNS_RESOURCE_RECORD_H
