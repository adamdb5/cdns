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
#include <arpa/inet.h>
#include "a.h"

static void aaaa_cast_to_resource(void **state) {
  DNSARecord a;
  DNSResourceRecord r;
  int matching = 1;

  memset(&a, 0, sizeof(DNSARecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(a.name, "adambruce.net");
  a.type = TYPE_A;
  a.class = CLASS_IN;
  a.ttl = 300;
  inet_pton(AF_INET, "1.1.1.1", &a.address);

  dns_cast_a_to_resource(&r, &a);

  if (strcmp(a.name, r.name) != 0) matching = 0;
  if (a.type != r.type) matching = 0;
  if (a.class != r.class) matching = 0;
  if (a.ttl != r.ttl) matching = 0;
  if (r.rdlength != 4) matching = 0;
  if (memcmp(&a.address, r.rdata, 4) != 0) matching = 0;

  assert_true(matching);
}

static void resource_cast_to_a(void **state) {
  DNSARecord a;
  DNSResourceRecord r;
  int matching = 1;

  memset(&a, 0, sizeof(DNSARecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(r.name, "adambruce.net");
  r.type = TYPE_A;
  r.class = CLASS_IN;
  r.ttl = 300;
  r.rdlength = 4;
  memcpy(r.rdata, "\x01\x01\x01\x01", 4);

  dns_cast_resource_to_a(&a, &r);

  if (strcmp(a.name, r.name) != 0) matching = 0;
  if (a.type != r.type) matching = 0;
  if (a.class != r.class) matching = 0;
  if (a.ttl != r.ttl) matching = 0;
  if (memcmp(&a.address, r.rdata, 4) != 0) matching = 0;

  assert_true(matching);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(aaaa_cast_to_resource),
      cmocka_unit_test(resource_cast_to_a),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
