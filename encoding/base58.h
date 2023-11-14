#ifndef CRYPTOGRAPHY_ENCODING_BASE58_H
#define CRYPTOGRAPHY_ENCODING_BASE58_H

// base58 with bitcoin alphabet, base58check adds 4 bytes of double sha256

#include <algorithm>
#include <string>

#include "common/hex.h"
#include "hash/sha256.h"

inline std::string base58Encode(const Bytes& bytes) {
    const char* alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

    size_t zeros = 0;

    while (zeros < bytes.size() && bytes[zeros] == 0) {
        zeros++;
    }

    BigInt value = bytesToBigInt(bytes);
    std::string result;

    while (value > 0) {
        BigInt rem = value % 58;
        value /= 58;
        result += alphabet[rem.convert_to<int>()];
    }
    result.append(zeros, '1');
    std::reverse(result.begin(), result.end());

    return result;
}

inline int base58CharIndex(char c) {
    const char* alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

    for (int i = 0; i < 58; i++) {
        if (alphabet[i] == c) {
            return i;
        }
    }

    return -1;
}

inline Bytes base58Decode(const std::string& text) {
    size_t ones = 0;

    while (ones < text.size() && text[ones] == '1') {
        ones++;
    }

    BigInt value = 0;

    for (size_t i = ones; i < text.size(); i++) {
        value = value * 58 + base58CharIndex(text[i]);
    }

    Bytes body;

    while (value > 0) {
        BigInt rem = value % 256;
        value /= 256;
        body.push_back(rem.convert_to<uint8_t>());
    }
    std::reverse(body.begin(), body.end());

    Bytes result(ones, 0);
    result.insert(result.end(), body.begin(), body.end());

    return result;
}

inline std::string base58Check(const Bytes& payload) {
    Bytes hash1 = sha256(payload);
    Bytes hash2 = sha256(hash1);
    Bytes data = payload;
    data.insert(data.end(), hash2.begin(), hash2.begin() + 4);

    return base58Encode(data);
}

#endif
