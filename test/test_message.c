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

#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include <string.h>
#include <arpa/inet.h>

#include "message.h"
#include "records/a.h"

static void message_pack_header(void **state) {
  DNSMessage message;
  char buffer[512];
  char expected[] = "\xbe\xef\x10\x04\x00\x01\x00\x00\x00\x05\x00\x00";

  memset(&message, 0, sizeof(DNSMessage));
  message.header.id = 0xbeef;
  message.header.opcode = OPCODE_STATUS;
  message.header.rcode = RCODE_NOT_IMPLEMENTED;
  message.header.qdcount = 1;
  message.header.nscount = 5;

  memset(&buffer, 0, 512);
  dns_message_pack(buffer, &message);
  assert_memory_equal(buffer, &expected, 12);
}

static void message_pack_question(void **state) {
  DNSMessage message;
  char buffer[512];
  char expected[] = "\x09\x61\x64\x61\x6d\x62\x72\x75\x63\x65\x03\x6e\x65\x74"
                    "\x00\x00\x1c\x00\x01";

  memset(&message, 0, sizeof(DNSMessage));
  message.header.id = 0xbeef;
  message.header.qdcount = 1;

  strcpy(message.question.qname, "adambruce.net");
  message.question.qtype = TYPE_AAAA;
  message.question.qclass = CLASS_IN;

  memset(&buffer, 0, 512);
  dns_message_pack(buffer, &message);
  assert_memory_equal(buffer + 12, &expected, 19);
}

static void message_pack_answers(void **state) {
  DNSMessage message;
  DNSARecord a_record;
  DNSResourceRecord r_record;
  char buffer[512];
  char expected[] = "\x03\x61\x70\x69\x06\x67\x69\x74\x68\x75\x62\x03\x63\x6f"
                    "\x6d\x00\x00\x01\x00\x01";

  memset(&message, 0, sizeof(DNSMessage));
  message.header.id = 0x7671;
  message.header.qr = 1;
  message.header.rd = 1;
  message.header.qdcount = 1;
  message.header.ancount = 1;

  strcpy(message.question.qname, "api.github.com");
  message.question.qtype = TYPE_A;
  message.question.qclass = CLASS_IN;

  memset(&a_record, 0, sizeof(DNSARecord));
  memset(&r_record, 0, sizeof(DNSResourceRecord));

  strcpy(a_record.name, "api.github.com");
  inet_pton(AF_INET, "140.82.121.5", &a_record.address);
  a_record.ttl = 300;
  a_record.type = TYPE_A;
  a_record.class = CLASS_IN;

  dns_cast_a_to_resource(&r_record, &a_record);
  message.answers[0] = r_record;

  memset(&buffer, 0, 512);
  dns_message_pack(buffer, &message);
  assert_memory_equal(buffer + 32, &expected, 19);
}

static void message_unpack_header(void **state) {
  DNSMessage message;
  char buffer[] = "\xbe\xef\x10\x04\x00\x00\x00\x00\x00\x00\x00\x00";

  memset(&message, 0, sizeof(DNSMessage));

  dns_message_unpack(&message, buffer);

  assert_true(message.header.id = 0xbeef);
}

static void message_unpack_question(void **state) {
  DNSMessage message;
  char buffer[] = "\xbe\xef\x10\x04\x00\x01\x00\x00\x00\x00\x00\x00\x03\x61"
                  "\x70\x69\x06\x67\x69\x74\x68\x75\x62\x03\x63\x6f\x6d\x00"
                  "\x00\x01\x00\x01";

  memset(&message, 0, sizeof(DNSMessage));
  dns_message_unpack(&message, buffer);

  assert_true(strcmp(message.question.qname, "api.github.com") == 0
              && message.question.qtype == TYPE_A
              && message.question.qclass == CLASS_IN);
}

static void message_unpack_answers(void **state) {
  DNSMessage message;
  DNSARecord a_record;
  in_addr_t expected;

  char buffer[] = "\x76\x71\x81\x00\x00\x01\x00\x01\x00\x00\x00\x00\x03\x61"
                  "\x70\x69\x06\x67\x69\x74\x68\x75\x62\x03\x63\x6f\x6d\x00"
                  "\x00\x01\x00\x01\xc0\x0c\x00\x01\x00\x01\x00\x00\x01\x2c"
                  "\x00\x04\x8c\x52\x79\x05";

  memset(&message, 0, sizeof(DNSMessage));
  dns_message_unpack(&message, buffer);

  dns_cast_resource_to_a(&a_record, &message.answers[0]);

  inet_pton(AF_INET, "140.82.121.5", &expected);
  assert_true(
      strcmp(a_record.name, "api.github.com") == 0
      && a_record.ttl == 300
      && a_record.class == CLASS_IN
      && a_record.type == TYPE_A
      && a_record.address == expected);
}

static void message_pack_byte_count(void **state) {
  DNSMessage message;
  DNSARecord a_record;
  DNSResourceRecord r_record;
  size_t byte_count;
  char buffer[512];

  memset(&message, 0, sizeof(DNSMessage));
  message.header.id = 0x7671;
  message.header.qr = 1;
  message.header.rd = 1;
  message.header.qdcount = 1;
  message.header.ancount = 1;

  strcpy(message.question.qname, "api.github.com");
  message.question.qtype = TYPE_A;
  message.question.qclass = CLASS_IN;

  memset(&a_record, 0, sizeof(DNSARecord));
  memset(&r_record, 0, sizeof(DNSResourceRecord));

  strcpy(a_record.name, "api.github.com");
  inet_pton(AF_INET, "140.82.121.5", &a_record.address);
  a_record.ttl = 300;
  a_record.type = TYPE_A;
  a_record.class = CLASS_IN;

  dns_cast_a_to_resource(&r_record, &a_record);
  message.answers[0] = r_record;

  memset(&buffer, 0, 512);
  byte_count = dns_message_pack(buffer, &message);

  assert_int_equal(byte_count, 60);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(message_pack_header),
      cmocka_unit_test(message_pack_question),
      cmocka_unit_test(message_pack_answers),

      cmocka_unit_test(message_unpack_header),
      cmocka_unit_test(message_unpack_question),
      cmocka_unit_test(message_unpack_answers),

      cmocka_unit_test(message_pack_byte_count),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
