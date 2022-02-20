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

#include "resource_record.h"
#include "question.h"
#include <netinet/in.h>
#include <string.h>

size_t dns_resource_record_pack(char *bytes, const DNSResourceRecord *record) {
  size_t i = 0;
  char *name_token;
  char temp_str[512];

  strcpy(temp_str, record->name);
  name_token = strtok(temp_str, ".");
  while (name_token != NULL) {
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

size_t dns_resource_record_unpack(DNSResourceRecord *record, const char *bytes,
                                  const char *message_root) {
  size_t i = 0;
  size_t ptr_i = 0;
  int is_pointer = 0;
  uint16_t offset;
  while (bytes[i] != '\0') {
    char part_len = bytes[i++];

    if (part_len & 0xC0) {
      is_pointer = 1;
      offset = htons((part_len & 0x3F) | (bytes[i++] << 8));
      break;
    }

    strncat(record->name, bytes + i, part_len);
    i += part_len;
    strcat(record->name, ".");
  }

  if (is_pointer) {
    while (message_root[offset + ptr_i] != '\0') {
      char part_len = message_root[offset + ptr_i];
      ptr_i++;
      strncat(record->name, message_root + offset + ptr_i, part_len);
      ptr_i += part_len;
      strcat(record->name, ".");
    }
    ptr_i -= 2;
  }

  record->name[i + ptr_i - 1] = '\0';
  record->type = htons(*(uint16_t *)(bytes + i));
  i += 2;
  record->class = htons(*(uint16_t *)(bytes + i));
  i += 2;
  record->ttl = htonl(*(uint32_t *)(bytes + i));
  i += 4;
  record->rdlength = htons(*(uint16_t *)(bytes + i));
  i += 2;

  memcpy(record->rdata, bytes + i, record->rdlength);

  /* TODO: Work out why our reported length is 8 bytes too short */
  return i + ptr_i + 8;
}
