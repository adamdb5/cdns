//
// Created by adam on 18/02/2022.
//

#include <string.h>
#include "question.h"

size_t dns_question_pack(char *bytes, const DNSQuestion *question) {
    size_t i = 0;
    char *name_token;
    char temp_str[strlen(question->qname) + 1];

    strcpy(temp_str, question->qname);
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
    bytes[i++] = (char)(question->qtype & (0xFF << 8));
    bytes[i++] = (char)(question->qtype & 0xFF);
    bytes[i++] = (char)(question->qclass & (0xFF << 8));
    bytes[i++] = (char)(question->qclass & 0xFF);

    return i;
}

size_t dns_question_unpack(DNSQuestion *question, const char *bytes) {

}

