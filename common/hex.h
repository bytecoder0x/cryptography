#ifndef CRYPTOGRAPHY_COMMON_HEX_H
#define CRYPTOGRAPHY_COMMON_HEX_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/bigint.h"

using Bytes = std::vector<uint8_t>;

inline std::string toHex(const Bytes& bytes) {
    const char* digits = "0123456789abcdef";
    std::string result;

    for (uint8_t b : bytes) {
        result += digits[b >> 4];
        result += digits[b & 15];
    }

    return result;
}

inline int hexValue(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }

    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }

    return 0;
}

// accepts both "ab12" and "0xab12"
inline Bytes fromHex(const std::string& hex) {
    size_t start = 0;

    if (hex.size() >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        start = 2;
    }
    Bytes result;

    for (size_t i = start; i + 1 < hex.size(); i += 2) {
        result.push_back(static_cast<uint8_t>(hexValue(hex[i]) * 16 + hexValue(hex[i + 1])));
    }

    return result;
}

inline Bytes toBytes(const std::string& text) {
    return Bytes(text.begin(), text.end());
}

// big-endian
inline BigInt bytesToBigInt(const Bytes& bytes) {
    BigInt result = 0;

    for (uint8_t b : bytes) {
        result = (result << 8) | b;
    }

    return result;
}

// big-endian, padded with zeros on the left
inline Bytes bigIntToBytes(const BigInt& value, size_t length) {
    Bytes result(length, 0);
    BigInt v = value;

    for (size_t i = 0; i < length && v > 0; i++) {
        BigInt low = v & 0xff;
        result[length - 1 - i] = low.convert_to<uint8_t>();
        v >>= 8;
    }

    return result;
}

#endif
