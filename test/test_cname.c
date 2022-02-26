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
#include "cname.h"
#include "question.h"

static void cname_cast_to_resource(void **state) {
  DNSCNameRecord c;
  DNSResourceRecord r;
  int matching = 1;

  memset(&c, 0, sizeof(DNSCNameRecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(c.name, "adambruce.net");
  c.type = TYPE_CNAME;
  c.class = CLASS_IN;
  c.ttl = 300;
  strcpy(c.cname, "cname.adambruce.net");

  dns_cast_cname_to_resource(&r, &c);

  if (strcmp(c.name, r.name) != 0) matching = 0;
  if (c.type != r.type) matching = 0;
  if (c.class != r.class) matching = 0;
  if (c.ttl != r.ttl) matching = 0;
  if (r.rdlength != 19) matching = 0;
  if (memcmp(&c.cname, r.rdata, r.rdlength) != 0) matching = 0;

  assert_true(matching);
}

static void resource_cast_to_cname(void **state) {
  DNSCNameRecord c;
  DNSResourceRecord r;
  int matching = 1;

  memset(&c, 0, sizeof(DNSCNameRecord));
  memset(&r, 0, sizeof(DNSResourceRecord));

  strcpy(r.name, "adambruce.net");

  r.type = TYPE_CNAME;
  r.class = CLASS_IN;
  r.ttl = 300;
  r.rdlength = 21;

  strcat(r.rdata, "\x05");
  strcat(r.rdata, "cname");
  strcat(r.rdata, "\x09");
  strcat(r.rdata, "adambruce");
  strcat(r.rdata, "\x03");
  strcat(r.rdata, "net");

  dns_cast_resource_to_cname(&c, &r, NULL);

  if (strcmp(c.name, r.name) != 0) matching = 0;
  if (c.type != r.type) matching = 0;
  if (c.class != r.class) matching = 0;
  if (c.ttl != r.ttl) matching = 0;
  if (strcmp(c.cname, "cname.adambruce.net") != 0) matching = 0;

  assert_true(matching);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(cname_cast_to_resource),
      cmocka_unit_test(resource_cast_to_cname),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
