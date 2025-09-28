//
// Created by arjun on 28/09/25.
//

#ifndef DNSPLAY_DNS_H
#define DNSPLAY_DNS_H

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// https://datatracker.ietf.org/doc/html/rfc1035#section-4.1.1
struct dns_header {
    uint16_t id;
    uint16_t flags;
    uint16_t qd_count;
    uint16_t an_count;
    uint16_t ns_count;
    uint16_t ar_count;
};

struct dns_question {
    string q_name;
    uint16_t q_type;
    uint16_t q_class;
};

struct dns_resource_record {
    string name;
    uint16_t type;
    uint16_t class_;
    uint32_t ttl;
    uint16_t rd_length;
    std::vector<uint8_t> r_data;
};

struct dns_message {
    dns_header header;
    dns_question question;
    dns_resource_record answer;
    dns_resource_record authority;
    dns_resource_record additional;
};

#endif