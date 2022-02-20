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

#include "a.h"
#include "resource_record.h"

void dns_cast_a_to_resource(DNSResourceRecord *resource_record,
                            const DNSARecord *a) {
  strcpy(resource_record->name, a->name);
  resource_record->type = TYPE_A;
  resource_record->class = CLASS_IN;
  resource_record->ttl = a->ttl;
  resource_record->rdlength = DNS_A_RECORD_ADDRESS_LENGTH;
  *(in_addr_t *)(resource_record->rdata) = a->address;
}

void dns_cast_resource_to_a(DNSARecord *a,
                            const DNSResourceRecord *resource_record) {
  strcpy(a->name, resource_record->name);
  a->type = resource_record->type;
  a->class = resource_record->class;
  a->ttl = resource_record->ttl;
  a->address = *(in_addr_t *)(resource_record->rdata);
}
