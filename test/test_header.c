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
#include <netinet/in.h>

#include "header.h"

static void header_flags_pack_qr(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.qr = 1;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x1 << 15)) >> 15, 1);
}

static void header_flags_pack_opcode(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.opcode = OPCODE_STATUS;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0xF << 11)) >> 11, OPCODE_STATUS);
}

static void header_flags_pack_aa(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.aa = 1;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x1 << 10)) >> 10, 1);
}

static void header_flags_pack_tc(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.tc = 1;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x1 << 9)) >> 9, 1);
}

static void header_flags_pack_rd(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.rd = 1;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x1 << 8)) >> 8, 1);
}

static void header_flags_pack_ra(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.ra = 1;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x1 << 7)) >> 7, 1);
}

static void header_flags_pack_z(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.z = 3;

  flags = dns_header_flags_pack(&header);
  assert_int_equal((flags & (0x7 << 4)) >> 4, 3);
}

static void header_flags_pack_rcode(void **state) {
  DNSHeader header;
  uint16_t flags;

  memset(&header, 0, sizeof(DNSHeader));
  header.rcode = RCODE_FORMAT_ERROR;

  flags = dns_header_flags_pack(&header);
  assert_int_equal(flags & 0xF, RCODE_FORMAT_ERROR);
}

static void header_flags_unpack_qr(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 1 << 15;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.qr, 1);
}

static void header_flags_unpack_opcode(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = OPCODE_STATUS << 11;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.opcode, OPCODE_STATUS);
}

static void header_flags_unpack_aa(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 1 << 10;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.aa, 1);
}

static void header_flags_unpack_tc(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 1 << 9;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.tc, 1);
}

static void header_flags_unpack_rd(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 1 << 8;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.rd, 1);
}

static void header_flags_unpack_ra(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 1 << 7;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.ra, 1);
}

static void header_flags_unpack_z(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = 3 << 4;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.z, 3);
}

static void header_flags_unpack_rcode(void **state) {
  DNSHeader header;
  uint16_t flags;

  flags = RCODE_FORMAT_ERROR;

  dns_header_flags_unpack(&header, flags);
  assert_int_equal(header.rcode, RCODE_FORMAT_ERROR);
}

static void header_pack_id(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.id = 0xbeef;

  dns_header_pack(buffer, &header);
  expected = htons(header.id);
  assert_memory_equal(buffer, &expected, 2);
}

static void header_pack_flags(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.opcode = OPCODE_STATUS;
  header.rcode = RCODE_NOT_IMPLEMENTED;

  dns_header_pack(buffer, &header);
  expected = htons(dns_header_flags_pack(&header));
  assert_memory_equal(buffer + 2, &expected, 2);
}

static void header_pack_qdcount(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.qdcount = 1;

  dns_header_pack(buffer, &header);
  expected = htons(header.qdcount);
  assert_memory_equal(buffer + 4, &expected, 1);
}

static void header_pack_ancount(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.ancount = 4;

  dns_header_pack(buffer, &header);
  expected = htons(header.ancount);
  assert_memory_equal(buffer + 6, &expected, 2);
}

static void header_pack_nscount(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.nscount = 5;

  dns_header_pack(buffer, &header);
  expected = htons(header.nscount);
  assert_memory_equal(buffer + 8, &expected, 2);
}

static void header_pack_arcount(void **state) {
  DNSHeader header;
  uint16_t expected;
  char buffer[512];

  memset(&header, 0, sizeof(DNSHeader));
  header.arcount = 6;

  dns_header_pack(buffer, &header);
  expected = htons(header.arcount);
  assert_memory_equal(buffer + 10, &expected, 2);
}

static void header_unpack_id(void **state) {
  DNSHeader header;
  char buffer[] = "\xbe\xef\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

  dns_header_unpack(&header, buffer);
  assert_int_equal(header.id, 0xbeef);
}

static void header_unpack_flags(void **state) {
  DNSHeader header;
  char buffer[] = "\x00\x00\x10\x04\x00\x00\x00\x00\x00\x00\x00\x00";

  dns_header_unpack(&header, buffer);
  assert_true(header.opcode == OPCODE_STATUS &&
              header.rcode == RCODE_NOT_IMPLEMENTED);
}

static void header_unpack_qdcount(void **state) {
  DNSHeader header;
  char buffer[] = "\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00";

  dns_header_unpack(&header, buffer);
  assert_int_equal(header.qdcount, 1);
}

static void header_unpack_ancount(void **state) {
  DNSHeader header;
  char buffer[] = "\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00";

  dns_header_unpack(&header, buffer);
  assert_int_equal(header.ancount, 4);
}

static void header_unpack_nscount(void **state) {
  DNSHeader header;
  char buffer[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00";

  dns_header_unpack(&header, buffer);
  assert_int_equal(header.nscount, 5);
}

static void header_unpack_arcount(void **state) {
  DNSHeader header;
  char buffer[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06";

  dns_header_unpack(&header, buffer);
  assert_int_equal(header.arcount, 6);
}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(header_flags_pack_qr),
    cmocka_unit_test(header_flags_pack_opcode),
    cmocka_unit_test(header_flags_pack_aa),
    cmocka_unit_test(header_flags_pack_tc),
    cmocka_unit_test(header_flags_pack_rd),
    cmocka_unit_test(header_flags_pack_ra),
    cmocka_unit_test(header_flags_pack_z),
    cmocka_unit_test(header_flags_pack_rcode),

    cmocka_unit_test(header_flags_unpack_qr),
    cmocka_unit_test(header_flags_unpack_opcode),
    cmocka_unit_test(header_flags_unpack_aa),
    cmocka_unit_test(header_flags_unpack_tc),
    cmocka_unit_test(header_flags_unpack_rd),
    cmocka_unit_test(header_flags_unpack_ra),
    cmocka_unit_test(header_flags_unpack_z),
    cmocka_unit_test(header_flags_unpack_rcode),

    cmocka_unit_test(header_pack_id),
    cmocka_unit_test(header_pack_flags),
    cmocka_unit_test(header_pack_qdcount),
    cmocka_unit_test(header_pack_ancount),
    cmocka_unit_test(header_pack_nscount),
    cmocka_unit_test(header_pack_arcount),

    cmocka_unit_test(header_unpack_id),
    cmocka_unit_test(header_unpack_flags),
    cmocka_unit_test(header_unpack_qdcount),
    cmocka_unit_test(header_unpack_ancount),
    cmocka_unit_test(header_unpack_nscount),
    cmocka_unit_test(header_unpack_arcount),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
