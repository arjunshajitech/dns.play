//
// Created by arjun on 29/09/25.
//

#ifndef DNSPLAY_DNS_RESPONSE_PACKET_H
#define DNSPLAY_DNS_RESPONSE_PACKET_H

#include <string>
#include <vector>

std::vector<uint8_t> build_response_packet(const char* query_buffer, const std::string& answer_text);

#endif