//
// Created by arjun on 27/09/25.
//

#include "includes/udp.h"
#include <iostream>
#include <ostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "includes/dns.h"
#include "includes/dns_parser.h"
#include "includes/dns_processor.h"

using namespace std;

int init_udp() {
    int sockfd;
    char buffer[MAX_LINE];
    sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr << "UDP Socket creation failed." << endl;
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, reinterpret_cast<const sockaddr *>(&server_addr), sizeof(server_addr)) < 0) {
        cerr << "UDP bind failed." << endl;
        close(sockfd);
        return 1;
    }

    cout << "Listening on UDP port: " << PORT << endl;

    while (true) {
        memset(buffer, 0, MAX_LINE);

        ssize_t bytes_received = recvfrom(sockfd, buffer, MAX_LINE - 1, 0,
                                          reinterpret_cast<struct sockaddr *>(&client_addr), &client_len);

        if (bytes_received < 0) {
            cerr << "Error receiving data." << endl;
            break;
        }

        dns_message message;

        cout << "Received " << bytes_received << " bytes" << endl;
        if (parse_dns_message(buffer, bytes_received, message)) {
            // For debug uncomment
            // print_dns_message(message);

            // Is dns packet is query packet 0 means query, 1 means response
            uint16_t qr = (message.header.flags >> 15) & 0x1;
            if (!qr) {
                string answer = process(message.header.id, message.question.q_name);
                vector<uint8_t> response = build_response(buffer, answer);

                ssize_t sent = sendto(sockfd, response.data(), response.size(), 0,
                                      reinterpret_cast<struct sockaddr *>(&client_addr), client_len);
                if (sent < 0) {
                    cerr << "Error sending response." << endl;
                }
            }
        }
    }

    close(sockfd);
    return 0;
}
