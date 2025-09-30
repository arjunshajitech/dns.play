cmake_minimum_required(VERSION 3.20)
project(dnsplay)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/uuid_v4)

add_executable(dnsplay main.cpp
        udp.cpp
        includes/dns.h
        includes/udp.h
        dns_processor.cpp
        includes/dns_processor.h
        rolldice.cpp
        includes/rolldice.h
        dns_response_packet.cpp
        includes/dns_response_packet.h
        dns_query_packet.cpp
        includes/dns_query_packet.h
        uuid.cpp
        includes/uuid.h
)

target_include_directories(dnsplay PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/external/uuid_v4
)

target_link_libraries(dnsplay PRIVATE uuid_v4::uuid_v4)
target_compile_options(dnsplay PRIVATE -mavx2)

