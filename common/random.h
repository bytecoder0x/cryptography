#ifndef CRYPTOGRAPHY_COMMON_RANDOM_H
#define CRYPTOGRAPHY_COMMON_RANDOM_H

#include <random>

#include "common/bigint.h"

inline std::mt19937_64& randomEngine() {
    static std::mt19937_64 engine{std::random_device{}()};
    return engine;
}

// random number with exactly `bits` bits, the top bit is always set
inline BigInt randomBits(int bits) {
    BigInt result = 0;
    int produced = 0;

    while (produced < bits) {
        result = (result << 64) | randomEngine()();
        produced += 64;
    }
    result >>= (produced - bits);
    result |= BigInt(1) << (bits - 1);

    return result;
}

// random number in [0, limit)
inline BigInt randomBelow(const BigInt& limit) {
    int bits = 0;
    BigInt t = limit;

    while (t > 0) {
        t >>= 1;
        bits++;
    }
    BigInt result = 0;

    for (int i = 0; i < bits / 64 + 2; i++) {
        result = (result << 64) | randomEngine()();
    }

    return result % limit;
}

#endif
