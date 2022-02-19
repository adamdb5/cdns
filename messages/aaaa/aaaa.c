//
// Created by adam on 19/02/2022.
//

#include "../../resource_record.h"
#include "aaaa.h"

void dns_cast_aaaa_to_resource(DNSResourceRecord *resource_record, const DNSAAAARecord *aaaa) {
    strcpy(resource_record->name, aaaa->name);
    resource_record->type = TYPE_AAAA;
    resource_record->class = CLASS_IN;
    resource_record->ttl = aaaa->ttl;
    resource_record->rdlength = DNS_AAAA_RECORD_ADDRESS_LENGTH;
    memcpy(resource_record->rdata, aaaa->address, DNS_AAAA_RECORD_ADDRESS_LENGTH);
}

void dns_cast_resource_to_aaaa(DNSAAAARecord *aaaa, const DNSResourceRecord *resource_record) {
    strcpy(aaaa->name, resource_record->name);
    aaaa->type = resource_record->type;
    aaaa->class = resource_record->class;
    aaaa->ttl = resource_record->ttl;
    memcpy(aaaa->address, resource_record->rdata, DNS_AAAA_RECORD_ADDRESS_LENGTH);
}