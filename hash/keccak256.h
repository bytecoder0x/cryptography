#ifndef CRYPTOGRAPHY_HASH_KECCAK256_H
#define CRYPTOGRAPHY_HASH_KECCAK256_H

// Keccak-256 like in Ethereum, not the same as sha3-256 (other padding byte)

#include <cstdint>

#include "common/hex.h"

const uint64_t KECCAK_RC[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a, 0x8000000080008000,
    0x000000000000808b, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008a, 0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080, 0x000000000000800a, 0x800000008000000a,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

const int KECCAK_ROTATION[25] = {
    0, 1, 62, 28, 27,
    36, 44, 6, 55, 20,
    3, 10, 43, 25, 39,
    41, 45, 15, 21, 8,
    18, 2, 61, 56, 14
};

inline uint64_t rotateLeft64(uint64_t x, int n) {
    if (n == 0) {
        return x;
    }
    return (x << n) | (x >> (64 - n));
}

// state is 5x5 lanes of 64 bits, lane (x, y) is stored at index x + 5 * y
inline void keccakF(uint64_t state[25]) {
    for (int round = 0; round < 24; round++) {
        // theta
        uint64_t c[5];
        for (int x = 0; x < 5; x++) {
            c[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];
        }
        for (int x = 0; x < 5; x++) {
            uint64_t d = c[(x + 4) % 5] ^ rotateLeft64(c[(x + 1) % 5], 1);
            for (int y = 0; y < 5; y++) {
                state[x + 5 * y] ^= d;
            }
        }

        // rho and pi
        uint64_t b[25];
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                b[y + 5 * ((2 * x + 3 * y) % 5)] = rotateLeft64(state[x + 5 * y], KECCAK_ROTATION[x + 5 * y]);
            }
        }

        // chi
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                state[x + 5 * y] = b[x + 5 * y] ^ (~b[(x + 1) % 5 + 5 * y] & b[(x + 2) % 5 + 5 * y]);
            }
        }

        // iota
        state[0] ^= KECCAK_RC[round];
    }
}

// paddingByte is 0x01 for Keccak-256 and 0x06 for SHA3-256
inline Bytes keccakSponge(const Bytes& data, uint8_t paddingByte) {
    const size_t rate = 136;
    uint64_t state[25] = {0};

    Bytes padded = data;
    padded.push_back(paddingByte);

    while (padded.size() % rate != 0) {
        padded.push_back(0);
    }
    padded[padded.size() - 1] |= 0x80;

    for (size_t offset = 0; offset < padded.size(); offset += rate) {
        for (size_t i = 0; i < rate / 8; i++) {
            uint64_t lane = 0;
            for (int j = 7; j >= 0; j--) {
                lane = (lane << 8) | padded[offset + 8 * i + j];
            }
            state[i] ^= lane;
        }
        keccakF(state);
    }

    Bytes digest;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            digest.push_back(uint8_t(state[i] >> (8 * j)));
        }
    }

    return digest;
}

inline Bytes keccak256(const Bytes& data) {
    return keccakSponge(data, 0x01);
}

#endif
