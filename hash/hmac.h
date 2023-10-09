#ifndef CRYPTOGRAPHY_HASH_HMAC_H
#define CRYPTOGRAPHY_HASH_HMAC_H

// HMAC-SHA256, RFC 2104

#include "common/hex.h"
#include "hash/sha256.h"

inline Bytes hmacSha256(const Bytes& key, const Bytes& data) {
    const size_t blockSize = 64;

    Bytes k = key;

    if (k.size() > blockSize) {
        k = sha256(k);
    }
    k.resize(blockSize, 0);

    Bytes inner(blockSize);
    Bytes outer(blockSize);

    for (size_t i = 0; i < blockSize; i++) {
        inner[i] = k[i] ^ 0x36;
        outer[i] = k[i] ^ 0x5c;
    }

    inner.insert(inner.end(), data.begin(), data.end());
    Bytes innerHash = sha256(inner);
    outer.insert(outer.end(), innerHash.begin(), innerHash.end());

    return sha256(outer);
}

#endif
