//
// Created by arjun on 28/09/25.
//

#ifndef DNSPLAY_DNS_PARSER_H
#define DNSPLAY_DNS_PARSER_H

#include "dns.h"

bool parse_dns_message(const char *buffer, size_t buffer_size, dns_message &message);

void print_dns_message(const dns_message& message);

vector<uint8_t> build_response(const char *buffer, const string &answer);

#endif