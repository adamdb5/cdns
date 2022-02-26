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
#include "cname.h"

void dns_cast_cname_to_resource(DNSResourceRecord *resource_record,
                             const DNSCNameRecord *cname) {
  strcpy(resource_record->name, cname->name);
  resource_record->type = TYPE_CNAME;
  resource_record->class = cname->class;
  resource_record->ttl = cname->ttl;
  resource_record->rdlength = strlen(cname->cname);
  memcpy(resource_record->rdata, cname->cname, resource_record->rdlength);
}

void dns_cast_resource_to_cname(DNSCNameRecord *cname,
                                const DNSResourceRecord *resource_record,
                                const char *message_root) {
  strcpy(cname->name, resource_record->name);
  cname->type = resource_record->type;
  cname->class = resource_record->class;
  cname->ttl = resource_record->ttl;

  dns_decompress_domain_name(cname->cname, resource_record->rdata,
                             message_root);
}
