//
// Created by arjun on 29/09/25.
//

#ifndef DNSPLAY_DNS_QUERY_PACKET_H
#define DNSPLAY_DNS_QUERY_PACKET_H

#include "dns.h"

bool parse_dns_query_packet(const char *query_buffer, dns_message &message);

void console_dns_packet(const dns_message &message);

#endif
