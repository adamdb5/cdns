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

#include "aaaa.h"
#include "resource_record.h"

void dns_cast_aaaa_to_resource(DNSResourceRecord *resource_record,
                               const DNSAAAARecord *aaaa) {
  strcpy(resource_record->name, aaaa->name);
  resource_record->type = TYPE_AAAA;
  resource_record->class = CLASS_IN;
  resource_record->ttl = aaaa->ttl;
  resource_record->rdlength = DNS_AAAA_RECORD_ADDRESS_LENGTH;
  memcpy(resource_record->rdata, aaaa->address, DNS_AAAA_RECORD_ADDRESS_LENGTH);
}

void dns_cast_resource_to_aaaa(DNSAAAARecord *aaaa,
                               const DNSResourceRecord *resource_record) {
  strcpy(aaaa->name, resource_record->name);
  aaaa->type = resource_record->type;
  aaaa->class = resource_record->class;
  aaaa->ttl = resource_record->ttl;
  memcpy(aaaa->address, resource_record->rdata, DNS_AAAA_RECORD_ADDRESS_LENGTH);
}
