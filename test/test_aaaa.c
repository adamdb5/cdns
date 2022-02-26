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
#include "aaaa.h"

static void aaaa_cast_to_resource(void **state) {
  DNSAAAARecord a;
  DNSResourceRecord r;
  int matching = 1;

  memset(&a, 0, sizeof(DNSAAAARecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(a.name, "adambruce.net");
  a.type = TYPE_AAAA;
  a.class = CLASS_IN;
  a.ttl = 300;
  inet_pton(AF_INET6, "2001:19f0:7400:8b1a:5400:3ff:fe46:a56d", &a.address);

  dns_cast_aaaa_to_resource(&r, &a);

  if (strcmp(a.name, r.name) != 0) matching = 0;
  if (a.type != r.type) matching = 0;
  if (a.class != r.class) matching = 0;
  if (a.ttl != r.ttl) matching = 0;
  if (r.rdlength != DNS_AAAA_RECORD_ADDRESS_LENGTH) matching = 0;
  if (memcmp(&a.address, r.rdata, DNS_AAAA_RECORD_ADDRESS_LENGTH) != 0) matching = 0;

  assert_true(matching);
}

static void resource_cast_to_aaaa(void **state) {
  DNSAAAARecord a;
  DNSResourceRecord r;
  int matching = 1;

  memset(&a, 0, sizeof(DNSAAAARecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(r.name, "adambruce.net");
  r.type = TYPE_AAAA;
  r.class = CLASS_IN;
  r.ttl = 300;
  r.rdlength = 4;
  memcpy(r.rdata, "\x01\x01\x01\x01", 4);

  dns_cast_resource_to_aaaa(&a, &r);

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
      cmocka_unit_test(resource_cast_to_aaaa),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
