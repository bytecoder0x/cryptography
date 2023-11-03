#ifndef CRYPTOGRAPHY_PUBLIC_KEY_ECDSA_H
#define CRYPTOGRAPHY_PUBLIC_KEY_ECDSA_H

// ECDSA on secp256k1, the curve from Bitcoin and Ethereum

#include "common/bigint.h"
#include "common/hex.h"
#include "common/modular.h"
#include "common/random.h"

const BigInt SECP256K1_P("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
const BigInt SECP256K1_N("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
const BigInt SECP256K1_B = 7;

struct Point {
    BigInt x;
    BigInt y;
    bool infinity;
};

const Point SECP256K1_G = {
    BigInt("0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"),
    BigInt("0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"),
    false
};

struct Signature {
    BigInt r;
    BigInt s;
    int v;
};

inline BigInt modP(const BigInt& a) {
    return ((a % SECP256K1_P) + SECP256K1_P) % SECP256K1_P;
}

inline Point pointAdd(const Point& a, const Point& b) {
    if (a.infinity) {
        return b;
    }

    if (b.infinity) {
        return a;
    }
    BigInt lambda;

    if (a.x == b.x) {
        if (modP(a.y + b.y) == 0) {
            return {0, 0, true};
        }
        lambda = modP(3 * a.x * a.x * modinv(2 * a.y, SECP256K1_P));
    } else {
        lambda = modP((b.y - a.y) * modinv(b.x - a.x, SECP256K1_P));
    }
    BigInt x = modP(lambda * lambda - a.x - b.x);
    BigInt y = modP(lambda * (a.x - x) - a.y);

    return {x, y, false};
}

inline Point scalarMul(const BigInt& k, const Point& p) {
    Point result = {0, 0, true};
    Point current = p;
    BigInt bits = k;

    while (bits > 0) {
        if ((bits & 1) == 1) {
            result = pointAdd(result, current);
        }
        current = pointAdd(current, current);
        bits >>= 1;
    }

    return result;
}

inline BigInt generatePrivateKey() {
    return randomBelow(SECP256K1_N - 1) + 1;
}

inline Point publicKey(const BigInt& privateKey) {
    return scalarMul(privateKey, SECP256K1_G);
}

inline Signature sign(const Bytes& hash32, const BigInt& privateKey) {
    const BigInt& n = SECP256K1_N;
    BigInt z = bytesToBigInt(hash32);
    Signature sig = {0, 0, 0};

    while (true) {
        BigInt k = randomBelow(n - 1) + 1;
        Point point = scalarMul(k, SECP256K1_G);
        sig.r = point.x % n;
        sig.s = modinv(k, n) * (z + sig.r * privateKey) % n;
        if (sig.r == 0 || sig.s == 0) {
            continue;
        }
        sig.v = ((point.y & 1) == 1) ? 28 : 27;
        if (sig.s > n / 2) {
            sig.s = n - sig.s;
            sig.v = (sig.v == 27) ? 28 : 27;
        }
        return sig;
    }
}

inline bool verify(const Bytes& hash32, const Signature& sig, const Point& pub) {
    const BigInt& n = SECP256K1_N;

    if (sig.r < 1 || sig.r >= n || sig.s < 1 || sig.s >= n) {
        return false;
    }
    BigInt z = bytesToBigInt(hash32);
    BigInt w = modinv(sig.s, n);
    Point point = pointAdd(scalarMul(z * w % n, SECP256K1_G), scalarMul(sig.r * w % n, pub));

    if (point.infinity) {
        return false;
    }

    return point.x % n == sig.r;
}

#endif
