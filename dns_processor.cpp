//
// Created by arjun on 28/09/25.
//

#include <string>
#include <iostream>
#include "includes/rolldice.h"

enum QueryType { UUID, ULID, ROLL_DICE, UNKNOWN };

QueryType getQueryType(const std::string &q) {
    if (q == "uuid") return UUID;
    if (q == "ulid") return ULID;
    if (q == "rolldice") return ROLL_DICE;
    return UNKNOWN;
}

std::pair<std::string, int> split_at_dot(const std::string &input) {
    try {
        size_t pos = input.find('.');
        if (pos == std::string::npos) {
            return {input, 0};
        }
        std::string token = input.substr(0, pos);
        std::string count_after_dot = input.substr(pos + 1);
        return {token, std::stoi(count_after_dot)};
    } catch (...) {
        return {input, 0};
    }
}



std::string process(const uint16_t id, const std::string &query) {
    std::cout << "id: " << id << ", query: " << query << std::endl;
    // auto [q, count] = split_at_dot(query);

    switch (getQueryType(query)) {
        case UUID:
            break;
        case ULID:
            std::cout << "It's a Ulid!" << std::endl;
            break;
        case ROLL_DICE: {
            return roll_dice();
        }
        default:
            std::cout << "Unknown case" << std::endl;
    }

    return "";
}
