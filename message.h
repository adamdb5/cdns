//
// Created by adam on 19/02/2022.
//

#ifndef CDNS_MESSAGE_H
#define CDNS_MESSAGE_H

#include "header.h"
#include "question.h"

typedef struct {
    DNSHeader header;
    DNSQuestion question;
} DNSMessage;

size_t dns_message_unpack(DNSMessage *message, const char *buffer);
size_t dns_message_pack(char *buffer, const DNSMessage *message);

#endif //CDNS_MESSAGE_H
