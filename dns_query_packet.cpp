//
// Created by arjun on 29/09/25.
//

#include <netinet/in.h>
#include "includes/dns.h"

using namespace std;

pair<string, size_t> qname_to_string(const char *buffer, size_t pos) {
    string name;
    const size_t start = pos;
    while (buffer[pos] != 0) {
        const uint8_t len = buffer[pos++];
        if (!name.empty()) name += '.';
        name.append(buffer + pos, len);
        pos += len;
    }
    pos += 1;
    return {name, pos - start};
}

// https://datatracker.ietf.org/doc/html/rfc1035#section-4.1

bool parse_dns_query_packet(const char *query_buffer, dns_message &message) {
    try {
        size_t pos = 0;

        // https://datatracker.ietf.org/doc/html/rfc1035#section-4.1.1

        message.header.id = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;
        message.header.flags = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;
        message.header.qd_count = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;
        message.header.an_count = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;
        message.header.ns_count = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;
        message.header.ar_count = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        pos += 2;

        // https://datatracker.ietf.org/doc/html/rfc1035#section-4.1.2

        if (message.header.qd_count > 0) {
            auto [domain, qname_len] = qname_to_string(query_buffer, pos);
            message.question.q_name = domain;
            pos += qname_len;
            message.question.q_type = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
            pos += 2;
            message.question.q_class = ntohs(*reinterpret_cast<const uint16_t *>(query_buffer + pos));
        }

        return true;
    } catch (...) {
        return false;
    }
}

void console_dns_packet(const dns_message &message) {
    cout << "header:\n";
    cout << "  id: " << message.header.id << "\n";

    const uint16_t qr = (message.header.flags >> 15) & 0x1;
    cout << "  QR: " << qr << " (" << (qr ? "Response" : "Query") << ")\n";

    const uint16_t opcode = (message.header.flags >> 11) & 0xF;
    string opcode_str;
    switch (opcode) {
        case 0: opcode_str = "QUERY (standard query)";
            break;
        case 1: opcode_str = "IQUERY (inverse query)";
            break;
        case 2: opcode_str = "STATUS (server status request)";
            break;
        default: opcode_str = "Reserved";
            break;
    }
    cout << "  OPCODE: " << opcode << " (" << opcode_str << ")\n";

    const uint16_t aa = (message.header.flags >> 10) & 0x1;
    cout << "  AA: " << aa << " (" << (aa ? "Authoritative Answer" : "Not Authoritative") << ")\n";

    const uint16_t tc = (message.header.flags >> 9) & 0x1;
    cout << "  TC: " << tc << " (" << (tc ? "Truncated" : "Not Truncated") << ")\n";

    const uint16_t rd = (message.header.flags >> 8) & 0x1;
    cout << "  RD: " << rd << " (" << (rd ? "Recursion Desired" : "No Recursion Desired") << ")\n";

    const uint16_t ra = (message.header.flags >> 7) & 0x1;
    cout << "  RA: " << ra << " (" << (ra ? "Recursion Available" : "Recursion Not Available") << ")\n";

    const uint16_t z = (message.header.flags >> 4) & 0x7;
    cout << "  Z: " << z << " (Reserved, must be 0)\n";

    const uint16_t rcode = message.header.flags & 0xF;
    string rcode_str;
    switch (rcode) {
        case 0: rcode_str = "No error";
            break;
        case 1: rcode_str = "Format error";
            break;
        case 2: rcode_str = "Server failure";
            break;
        case 3: rcode_str = "Name Error";
            break;
        case 4: rcode_str = "Not Implemented";
            break;
        case 5: rcode_str = "Refused";
            break;
        default: rcode_str = "Reserved";
            break;
    }
    cout << "  RCODE: " << rcode << " (" << rcode_str << ")\n";

    cout << "  qd_count: " << message.header.qd_count << "\n";
    cout << "  an_count: " << message.header.an_count << "\n";
    cout << "  ns_count: " << message.header.ns_count << "\n";
    cout << "  ar_count: " << message.header.ar_count << "\n";

    if (message.header.qd_count > 0) {
        cout << "question:\n";
        cout << "  q_name: " << message.question.q_name << "\n";
        cout << "  q_type: " << message.question.q_type << "\n";
        cout << "  q_class: " << message.question.q_class << "\n";
    }
}