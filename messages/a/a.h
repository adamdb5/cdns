//
// Created by adam on 19/02/2022.
//

#ifndef CDNS_A_H
#define CDNS_A_H

#include <netinet/in.h>
#include <string.h>
#include "../../resource_record.h"
#include "../../question.h"

#define DNS_A_RECORD_ADDRESS_LENGTH 4

typedef struct {
    char name[255];
    uint16_t type;
    uint16_t class;
    uint16_t ttl;
    in_addr_t address;
} DNSARecord;

void dns_cast_a_to_resource(DNSResourceRecord *resource_record, const DNSARecord *a);
void dns_cast_resource_to_a(DNSARecord *a, const DNSResourceRecord *resource_record);

#endif //CDNS_A_H
