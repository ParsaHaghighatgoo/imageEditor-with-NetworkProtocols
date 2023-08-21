cmake_minimum_required(VERSION 3.24)
project(networkingphotoshopproject C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(networkingphotoshopproject main.c)

target_link_libraries(networkingphotoshopproject PRIVATE ${CURL_LIBRARIES} ws2_32)