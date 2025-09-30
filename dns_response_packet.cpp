//
// Created by arjun on 29/09/25.
//

#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>


void append_uint16(std::vector<uint8_t>& vec, uint16_t value) {
    vec.push_back((value >> 8) & 0xFF);
    vec.push_back(value & 0xFF);
}

void append_uint32(std::vector<uint8_t>& vec, uint32_t value) {
    vec.push_back((value >> 24) & 0xFF);
    vec.push_back((value >> 16) & 0xFF);
    vec.push_back((value >> 8) & 0xFF);
    vec.push_back(value & 0xFF);
}

// https://datatracker.ietf.org/doc/html/rfc1035#section-4.1

/*
* +---------------------+
    |        Header       |
    +---------------------+
    |       Question      | the question for the name server
    +---------------------+
    |        Answer       | RRs answering the question
    +---------------------+
    |      Authority      | RRs pointing toward an authority
    +---------------------+
    |      Additional     | RRs holding additional information
    +---------------------+
 */

std::vector<uint8_t> build_response_packet(const char* query_buffer, const std::string& answer_text) {
    std::vector<uint8_t> response;

    response.reserve(512); // Typical DNS packet size

    /* Header section format
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     */

    response.push_back(query_buffer[0]);
    response.push_back(query_buffer[1]);
    response.push_back(0x81);
    response.push_back(0x80);
    append_uint16(response, 1);
    append_uint16(response, 1);
    append_uint16(response, 0);
    append_uint16(response, 0);

    /* Question section format
    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                     QNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QTYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QCLASS                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     */

    size_t pos = 12;
    while (query_buffer[pos] != 0) {
        response.push_back(query_buffer[pos++]);
    }
    response.push_back(0);
    pos++;
    response.push_back(query_buffer[pos++]);
    response.push_back(query_buffer[pos++]);
    response.push_back(query_buffer[pos++]);
    response.push_back(query_buffer[pos]);

    /* Resource record format
    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                                               /
    /                      NAME                     /
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     CLASS                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TTL                      |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                   RDLENGTH                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
    /                     RDATA                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     */

    append_uint16(response, 0xC00C);
    append_uint16(response, 0x0010); // TXT 16 text strings
    append_uint16(response, 0x0001); // IN  1 the Internet
    append_uint32(response, 0); // No cache
    append_uint16(response, answer_text.size() + 1);
    response.push_back(answer_text.size());
    for (size_t i = 0; i < strlen(answer_text.c_str()); i++) {
        response.push_back(answer_text[i]);
    }

    return response;
};
