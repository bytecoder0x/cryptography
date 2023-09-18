#ifndef CRYPTOGRAPHY_HASH_SHA256_H
#define CRYPTOGRAPHY_HASH_SHA256_H

// SHA-256, FIPS 180-2

#include <cstdint>

#include "common/hex.h"

const uint32_t SHA256_K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const uint32_t SHA256_INIT[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

inline uint32_t rotateRight(uint32_t x, int n) {
    return (x >> n) | (x << (32 - n));
}

inline void sha256Block(uint32_t state[8], const uint8_t* block) {
    uint32_t w[64];

    for (int i = 0; i < 16; i++) {
        w[i] = (uint32_t(block[4 * i]) << 24) | (uint32_t(block[4 * i + 1]) << 16) |
               (uint32_t(block[4 * i + 2]) << 8) | uint32_t(block[4 * i + 3]);
    }

    for (int i = 16; i < 64; i++) {
        uint32_t s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t e = state[4];
    uint32_t f = state[5];
    uint32_t g = state[6];
    uint32_t h = state[7];

    for (int i = 0; i < 64; i++) {
        uint32_t s1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + s1 + ch + SHA256_K[i] + w[i];
        uint32_t s0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = s0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

inline Bytes sha256(const Bytes& data) {
    uint32_t state[8];

    for (int i = 0; i < 8; i++) {
        state[i] = SHA256_INIT[i];
    }

    // padding: 0x80, zeros up to 56 mod 64, then message length in bits (big-endian)
    Bytes padded = data;
    uint64_t bitLength = uint64_t(data.size()) * 8;
    padded.push_back(0x80);

    while (padded.size() % 64 != 56) {
        padded.push_back(0);
    }

    for (int i = 7; i >= 0; i--) {
        padded.push_back(uint8_t(bitLength >> (8 * i)));
    }

    for (size_t offset = 0; offset < padded.size(); offset += 64) {
        sha256Block(state, &padded[offset]);
    }

    Bytes digest;

    for (int i = 0; i < 8; i++) {
        digest.push_back(uint8_t(state[i] >> 24));
        digest.push_back(uint8_t(state[i] >> 16));
        digest.push_back(uint8_t(state[i] >> 8));
        digest.push_back(uint8_t(state[i]));
    }

    return digest;
}

#endif
