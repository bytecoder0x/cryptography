#ifndef CRYPTOGRAPHY_COMMON_PRIME_H
#define CRYPTOGRAPHY_COMMON_PRIME_H

#include "common/bigint.h"
#include "common/modular.h"
#include "common/random.h"

// Miller-Rabin test
inline bool isProbablePrime(const BigInt& n, int rounds = 20) {
    if (n < 2) {
        return false;
    }
    int smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (int p : smallPrimes) {
        if (n == p) {
            return true;
        }
        if (n % p == 0) {
            return false;
        }
    }

    // n - 1 = d * 2^r
    BigInt d = n - 1;
    int r = 0;

    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int i = 0; i < rounds; i++) {
        BigInt a = 2 + randomBelow(n - 3);
        BigInt x = modpow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }

    return true;
}

inline BigInt randomPrime(int bits) {
    while (true) {
        BigInt candidate = randomBits(bits) | 1;
        if (isProbablePrime(candidate)) {
            return candidate;
        }
    }
}

#endif
