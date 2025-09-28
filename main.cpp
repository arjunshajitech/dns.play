//
// Created by arjun on 27/09/25.
//

#include  <iostream>
#include "includes/udp.h"

using namespace std;

int main() {
    if (!init_udp()) {
        return -1;
    };
    return 0;
}
