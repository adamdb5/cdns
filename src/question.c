/*
 * Copyright (c) 2022 Adam Bruce
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string.h>
#include <netinet/in.h>
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
    size_t i = 0;
    while(bytes[i] != '\0') {
        char part_len = bytes[i++];
        strncat(question->qname, bytes + i, part_len);
        i += part_len;
        strcat(question->qname, ".");
    }
    question->qname[i - 1] = '\0';
    i++;
    question->qtype = htons(*(uint16_t*)(bytes + i));
    i += 2;
    question->qclass = htons(*(uint16_t*)(bytes + i));
    i += 2;
    return i;
}

