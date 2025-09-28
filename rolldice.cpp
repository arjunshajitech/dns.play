//
// Created by arjun on 28/09/25.
//


#include <string>

std::string roll_dice() {
    switch (rand() % 6 + 1) {
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        default: return "six";
    }
}
