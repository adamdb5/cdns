//
// Created by adam on 19/02/2022.
//

#include "message.h"

size_t dns_message_pack(char *buffer, const DNSMessage *message) {
    size_t len = 0;

    if(message->header.qdcount > 1)
        return 0; // Too many questions

    len += dns_header_pack(buffer, &message->header);
    len += dns_question_pack(buffer + len, &message->question);
    return len;
}

size_t dns_message_unpack(DNSMessage *message, const char *buffer) {
    size_t len = dns_header_unpack(&message->header, buffer);
    if(message->header.qdcount > 2)
        return 1; // Too many questions

    len += dns_question_unpack(&message->question, buffer);
    return len;
}
