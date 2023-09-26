#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
#include "common/modular.h"
#include "common/prime.h"
#include "hash/sha256.h"

using namespace std;

struct RsaKey {
    BigInt n;
    BigInt e;
    BigInt d;
};

RsaKey generateKey(int bits) {
    RsaKey key;
    key.e = 65537;
    while (true) {
        BigInt p = randomPrime(bits / 2);
        BigInt q = randomPrime(bits / 2);
        BigInt phi = (p - 1) * (q - 1);
        if (p != q && gcd(key.e, phi) == 1) {
            key.n = p * q;
            key.d = modinv(key.e, phi);
            return key;
        }
    }
}

BigInt encrypt(const BigInt& message, const RsaKey& key) {
    return modpow(message, key.e, key.n);
}

BigInt decrypt(const BigInt& ciphertext, const RsaKey& key) {
    return modpow(ciphertext, key.d, key.n);
}

// textbook signature without padding: hash^d mod n
BigInt signMessage(const string& message, const RsaKey& key) {
    BigInt hash = bytesToBigInt(sha256(toBytes(message)));
    return modpow(hash, key.d, key.n);
}

bool verifySignature(const string& message, const BigInt& signature, const RsaKey& key) {
    BigInt hash = bytesToBigInt(sha256(toBytes(message)));
    return modpow(signature, key.e, key.n) == hash;
}

int main() {
    RsaKey key = generateKey(1024);
    cout << "n = " << key.n << endl;
    cout << "e = " << key.e << endl;
    cout << "d = " << key.d << endl;

    BigInt message = 123456789;
    BigInt ciphertext = encrypt(message, key);
    cout << "message = " << message << endl;
    cout << "ciphertext = " << ciphertext << endl;
    cout << "decrypted = " << decrypt(ciphertext, key) << endl;

    string text = "hello rsa";
    BigInt signature = signMessage(text, key);
    cout << "signature = " << signature << endl;
    cout << "verify = " << verifySignature(text, signature, key) << endl;
    return 0;
}
