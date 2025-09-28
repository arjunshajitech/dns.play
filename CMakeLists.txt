cmake_minimum_required(VERSION 4.0)
project(dnsplay)

set(CMAKE_CXX_STANDARD 20)

add_executable(dnsplay main.cpp
        udp.cpp
        includes/dns.h
        includes/udp.h
        dns_parser.cpp
        includes/dns_parser.h
        dns_processor.cpp
        includes/dns_processor.h
        cmake-build-debug/rolldice.cpp
        cmake-build-debug/rolldice.h
        rootdice.cpp
        rootdice.h
        rolldice.cpp
        includes/rolldice.h
)
