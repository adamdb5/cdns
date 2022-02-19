//
// Created by adam on 19/02/2022.
//

#include <string.h>
#include <netinet/in.h>
#include "resource_record.h"
#include "question.h"

size_t dns_resource_record_pack(char *bytes, const DNSResourceRecord *record) {
    size_t i = 0;
    char *name_token;
    char temp_str[strlen(record->name) + 1];

    strcpy(temp_str, record->name);
    name_token = strtok(temp_str, ".");
    while(name_token != NULL) {
        char token_len = (char)strlen(name_token);
        bytes[i] = token_len;
        i++;
        strcpy(bytes + i, name_token);
        i += token_len;
        name_token = strtok(NULL, ".");
    }

    bytes[i++] = '\0';
    bytes[i++] = (char)(record->type & (0xFF << 8));
    bytes[i++] = (char)(record->type & 0xFF);
    bytes[i++] = (char)(record->class & (0xFF << 8));
    bytes[i++] = (char)(record->class & 0xFF);
    bytes[i++] = (char)(record->ttl & (0xFF << 8));
    bytes[i++] = (char)(record->ttl & 0xFF);
    bytes[i++] = (char)(record->rdlength & (0xFF << 8));
    bytes[i++] = (char)(record->rdlength & 0xFF);

    memcpy(bytes + i, record->rdata, record->rdlength);

    return i + record->rdlength;
}

size_t dns_resource_record_unpack(DNSResourceRecord *record, const char *bytes, const char *question_root) {
    size_t i = 0;
    size_t ptr_i = 0;
    int is_pointer = 0;
    uint16_t offset;
    while(bytes[i] != '\0') {
        char part_len = bytes[i++];

        if(part_len & 0b11000000) {
            is_pointer = 1;
            offset = htons((part_len & 0b00111111) | (bytes[i++] << 8));
            break;
        }

        strncat(record->name, bytes + i, part_len);
        i += part_len;
        strcat(record->name, ".");
    }

    if(is_pointer) {
        while(question_root[offset + ptr_i] != '\0') {
            char part_len = question_root[offset + ptr_i];
            ptr_i++;
            strncat(record->name, question_root + offset + ptr_i, part_len);
            ptr_i += part_len;
            strcat(record->name, ".");
        }
        ptr_i -= 2;
    }

    record->name[i + ptr_i - 1] = '\0';
    record->type = htons(*(uint16_t*)(bytes + i));
    i += 2;
    record->class = htons(*(uint16_t*)(bytes + i));
    i += 2;
    record->ttl = htonl(*(uint32_t*)(bytes + i));
    i += 4;
    record->rdlength = htons(*(uint16_t*)(bytes + i));
    i += 2;

    memcpy(record->rdata, bytes + i, record->rdlength);

    return i + ptr_i;
}