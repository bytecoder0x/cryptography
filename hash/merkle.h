#ifndef CRYPTOGRAPHY_HASH_MERKLE_H
#define CRYPTOGRAPHY_HASH_MERKLE_H

// merkle tree with sorted pairs, proof has no positions (like OpenZeppelin)

#include <vector>

#include "common/hex.h"
#include "hash/keccak256.h"

inline Bytes hashPair(const Bytes& a, const Bytes& b) {
    Bytes joined;

    if (a < b) {
        joined = a;
        joined.insert(joined.end(), b.begin(), b.end());
    } else {
        joined = b;
        joined.insert(joined.end(), a.begin(), a.end());
    }

    return keccak256(joined);
}

class MerkleTree {
public:
    explicit MerkleTree(const std::vector<Bytes>& leaves) {
        levels.push_back(leaves);
        while (levels.back().size() > 1) {
            const std::vector<Bytes>& current = levels.back();
            std::vector<Bytes> next;
            for (size_t i = 0; i < current.size(); i += 2) {
                if (i + 1 < current.size()) {
                    next.push_back(hashPair(current[i], current[i + 1]));
                } else {
                    next.push_back(current[i]);
                }
            }
            levels.push_back(next);
        }
    }

    Bytes root() const {
        return levels.back()[0];
    }

    std::vector<Bytes> proof(size_t index) const {
        std::vector<Bytes> result;
        for (size_t level = 0; level + 1 < levels.size(); level++) {
            size_t sibling = index ^ 1;
            if (sibling < levels[level].size()) {
                result.push_back(levels[level][sibling]);
            }
            index /= 2;
        }
        return result;
    }

    static bool verify(const Bytes& leaf, const std::vector<Bytes>& proof, const Bytes& root) {
        Bytes computed = leaf;
        for (size_t i = 0; i < proof.size(); i++) {
            computed = hashPair(computed, proof[i]);
        }
        return computed == root;
    }

private:
    std::vector<std::vector<Bytes>> levels;
};

#endif
