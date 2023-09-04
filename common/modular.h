#ifndef CRYPTOGRAPHY_COMMON_MODULAR_H
#define CRYPTOGRAPHY_COMMON_MODULAR_H

#include "common/bigint.h"

// square-and-multiply
inline BigInt modpow(BigInt base, BigInt exponent, const BigInt& modulus) {
    BigInt result = 1;
    base %= modulus;

    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            result = result * base % modulus;
        }
        base = base * base % modulus;
        exponent >>= 1;
    }

    return result;
}

inline BigInt gcd(BigInt a, BigInt b) {
    while (b != 0) {
        BigInt t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// extended Euclid: returns gcd(a, b) and finds x, y with a*x + b*y = gcd
inline BigInt egcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    BigInt x1, y1;
    BigInt g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// inverse of a modulo m, returns 0 when it does not exist
inline BigInt modinv(const BigInt& a, const BigInt& m) {
    BigInt x, y;
    BigInt g = egcd(((a % m) + m) % m, m, x, y);

    if (g != 1) {
        return 0;
    }

    return ((x % m) + m) % m;
}

#endif
