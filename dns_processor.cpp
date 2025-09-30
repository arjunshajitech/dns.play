//
// Created by arjun on 28/09/25.
//

#include <ctime>
#include <string>
#include "uuid_v4.h"
#include  "ulid.hh"

enum QueryType { UUID, COIN_TOSS, ROLL_DICE, UNIX, ULID, UNKNOWN };

QueryType getQueryType(const std::string &q) {
    if (q == "cointoss") return COIN_TOSS;
    if (q == "rolldice") return ROLL_DICE;
    if (q == "uuid") return UUID;
    if (q == "ulid") return ULID;
    if (q == "unix") return UNIX;
    return UNKNOWN;
}

std::pair<std::string, std::string> split_at_dot(const std::string &input) {
    try {
        size_t pos = input.find('.');
        if (pos == std::string::npos) {
            return {input, ""};
        }
        std::string token = input.substr(0, pos);
        std::string value = input.substr(pos + 1);
        return {token, value};
    } catch (...) {
        return {input, ""};
    }
}

std::string generate_uuid() {
    std::random_device rd;
    auto seed = rd();

    UUIDv4::UUIDGenerator<std::mt19937_64> generator(seed);
    UUIDv4::UUID uuid = generator.getUUID();

    return uuid.str();
}

std::string roll_dice() {
    switch (random() % 6 + 1) {
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        default: return "six";
    }
}

std::string coin_toss() {
    return (random() % 2 == 0) ? "Heads" : "Tails";
}

std::string unixToUTC(const std::string &unix_str) {
    try {
        time_t unix_time = std::stoll(unix_str);
        char buffer[30];
        std::tm *gmt = std::gmtime(&unix_time);
        if (gmt == nullptr) {
            return "Invalid unix timestamp";
        }
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", gmt);
        return std::string(buffer);
    } catch (...) {
        return "Invalid unix timestamp";
    }
}

std::string generate_ulid() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();

    ulid::ULID id = ulid::Create(ms, []() { return 4; });

    return ulid::Marshal(id);
}

std::string process(const uint16_t id, const std::string &query) {
    auto [q, v] = split_at_dot(query);

    switch (getQueryType(q)) {
        case ROLL_DICE: {
            return roll_dice();
        }
        case COIN_TOSS: {
            return coin_toss();
        }
        case UUID: {
            return generate_uuid();
        }
        case UNIX: {
            return unixToUTC(v);
        }
        case ULID: {
            return generate_ulid();
        }
        default:
            return "Invalid query";
    }
}
