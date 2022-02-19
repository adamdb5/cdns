//
// Created by adam on 19/02/2022.
//

#ifndef CDNS_AAAA_H
#define CDNS_AAAA_H

#include <netinet/in.h>
#include <string.h>
#include "../../resource_record.h"
#include "../../question.h"

#define DNS_AAAA_RECORD_ADDRESS_LENGTH 16

typedef struct {
    char name[255];
    uint16_t type;
    uint16_t class;
    uint16_t ttl;
    uint8_t address[DNS_AAAA_RECORD_ADDRESS_LENGTH];
} DNSAAAARecord;

void dns_cast_aaaa_to_resource(DNSResourceRecord *resource_record, const DNSAAAARecord *aaaa);
void dns_cast_resource_to_aaaa(DNSAAAARecord *aaaa, const DNSResourceRecord *resource_record);

#endif //CDNS_AAAA_H
