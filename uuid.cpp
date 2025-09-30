//
// Created by arjun on 30/09/25.
//

#include <uuid_v4.h>
#include <random>
#include <string>

std::string generateUUID() {
    std::random_device rd;
    auto seed = rd();

    UUIDv4::UUIDGenerator<std::mt19937_64> generator(seed);
    UUIDv4::UUID uuid = generator.getUUID();

    return uuid.str();
}

