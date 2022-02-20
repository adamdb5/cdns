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

#include "message.h"
#include "resource_record.h"
#include <string.h>

size_t dns_message_pack(char *bytes, const DNSMessage *message) {
  size_t cnt, len;

  if (message->header.qdcount > 1)
    return 0; /* Too many questions */

  len = dns_header_pack(bytes, &message->header);
  len += dns_question_pack(bytes + len, &message->question);

  for (cnt = 0; cnt < message->header.ancount && cnt < 10; cnt++) {
    len += dns_resource_record_pack(bytes + len, message->answers + cnt);
  }

  return len;
}

size_t dns_message_unpack(DNSMessage *message, const char *bytes) {
  size_t cnt, len;

  len = dns_header_unpack(&message->header, bytes);
  if (message->header.qdcount > 2)
    return 1;

  len += dns_question_unpack(&message->question, bytes + len);

  /* Answers */
  for (cnt = 0; cnt < message->header.ancount && cnt < 10; cnt++) {
    DNSResourceRecord record;
    memset(&record, 0, sizeof(DNSResourceRecord));
    len += dns_resource_record_unpack(&record, bytes + len, bytes);
    memcpy(message->answers + cnt, &record, sizeof(DNSResourceRecord));
  }
  return len;
}
