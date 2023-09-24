#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
#include "common/modular.h"
#include "common/prime.h"

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
    return 0;
}
