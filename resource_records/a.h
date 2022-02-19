//
// Created by adam on 19/02/2022.
//

#ifndef CDNS_A_H
#define CDNS_A_H

#include <netinet/in.h>
#include <string.h>
#include "../resource_record.h"
#include "../question.h"

#define DNS_A_RECORD_ADDRESS_LENGTH 4

typedef struct {
    char name[255];
    uint16_t type;
    uint16_t class;
    uint16_t ttl;
    in_addr_t address;
} DNSARecord;

void dns_cast_a_to_resource(DNSResourceRecord *resource_record, const DNSARecord *a) {
    strcpy(resource_record->name, a->name);
    resource_record->type = TYPE_A;
    resource_record->class = CLASS_IN;
    resource_record->ttl = a->ttl;
    resource_record->rdlength = DNS_A_RECORD_ADDRESS_LENGTH;
    *(in_addr_t *)(resource_record->rdata) = a->address;
}

void dns_cast_resource_to_a(DNSARecord *a, const DNSResourceRecord *resource_record) {
    strcpy(a->name, resource_record->name);
    a->type = resource_record->type;
    a->class = resource_record->class;
    a->ttl = resource_record->ttl;
    a->address = *(in_addr_t *)(resource_record->rdata);
}

#endif //CDNS_A_H
