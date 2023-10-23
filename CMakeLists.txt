cmake_minimum_required(VERSION 3.26)
project(cryptography)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
include_directories(${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(vigenere classical/vigenere.cpp)
add_executable(euclid number-theory/euclid.cpp)
add_executable(miller-rabin number-theory/miller-rabin.cpp)
add_executable(sha256 hash/sha256.cpp)
add_executable(rsa public-key/rsa.cpp)
add_executable(diffie-hellman public-key/diffie-hellman.cpp)
add_executable(hmac hash/hmac.cpp)
add_executable(keccak256 hash/keccak256.cpp)
add_executable(merkle hash/merkle.cpp)
