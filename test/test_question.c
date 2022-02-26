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

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>

#include "question.h"
#include "aaaa.h"
#include "a.h"

static void question_pack_qname(void **state) {
  DNSQuestion question;
  char buffer[512];
  char expected[15];

  memset(&question, 0, sizeof(DNSQuestion));
  strcpy(question.qname, "adambruce.net");
  sprintf(expected, "%cadambruce%cnet", 9, 3);

  dns_question_pack(buffer, &question);
  assert_memory_equal(buffer, &expected, 14);
}

static void question_pack_qtype(void **state) {
  DNSQuestion question;
  char buffer[512];
  uint16_t expected;

  memset(&question, 0, sizeof(DNSQuestion));
  strcpy(question.qname, "adambruce.net");
  question.qtype = TYPE_AAAA;

  dns_question_pack(buffer, &question);
  expected = htons(TYPE_AAAA);
  assert_memory_equal(buffer + 15, &expected, 2);
}

static void question_pack_qclass(void **state) {
  DNSQuestion question;
  char buffer[512];
  uint16_t expected;

  memset(&question, 0, sizeof(DNSQuestion));
  strcpy(question.qname, "adambruce.net");
  question.qtype = TYPE_AAAA;
  question.qclass = CLASS_IN;

  dns_question_pack(buffer, &question);
  expected = htons(CLASS_IN);
  assert_memory_equal(buffer + 17, &expected, 2);
}

static void question_unpack_qname(void **state) {
  DNSQuestion question;
  char buffer[512] = "\x09\x61\x64\x61\x6d\x62\x72\x75\x63\x65\x03\x6e\x65"
                     "\x74\x00\x00\x1c\x00\x01";
  char expected[14] = "adambruce.net";

  memset(&question, 0, sizeof(DNSQuestion));

  dns_question_unpack(&question, buffer);
  assert_memory_equal(question.qname, &expected, 13);
}

static void question_unpack_qtype(void **state) {
  DNSQuestion question;
  char buffer[512] = "\x09\x61\x64\x61\x6d\x62\x72\x75\x63\x65\x03\x6e\x65"
                     "\x74\x00\x00\x1c\x00\x01";

  dns_question_unpack(&question, buffer);
  assert_int_equal(question.qtype, TYPE_AAAA);
}

static void question_unpack_qclass(void **state) {
  DNSQuestion question;
  char buffer[512] = "\x09\x61\x64\x61\x6d\x62\x72\x75\x63\x65\x03\x6e\x65"
                     "\x74\x00\x00\x1c\x00\x01";

  dns_question_unpack(&question, buffer);
  assert_int_equal(question.qclass, CLASS_IN);
}

static void question_pack_byte_count_1(void **state) {
  DNSQuestion question;
  size_t byte_count;
  char buffer[512];

  strcpy(question.qname, "adambruce.net");
  question.qclass = CLASS_IN;
  question.qtype = TYPE_A;

  byte_count = dns_question_pack(buffer, &question);
  assert_int_equal(byte_count, 19);
}

static void question_unpack_byte_count_1(void **state) {
  DNSQuestion header;
  size_t byte_count;
  char buffer[] = "\x03\x61\x70\x69\x06\x67\x69\x74\x68\x75\x62\x03\x63\x6f"
                  "\x6d\x00\x00\x01\x00\x01";


  byte_count = dns_question_unpack(&header, buffer);
  assert_int_equal(byte_count, 20);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(question_pack_qname),
      cmocka_unit_test(question_pack_qtype),
      cmocka_unit_test(question_pack_qclass),

      cmocka_unit_test(question_unpack_qname),
      cmocka_unit_test(question_unpack_qtype),
      cmocka_unit_test(question_unpack_qclass),

      cmocka_unit_test(question_pack_byte_count_1),
      cmocka_unit_test(question_unpack_byte_count_1),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
