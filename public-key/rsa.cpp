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

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

string toHex(const BigInt& value, size_t length) {
    return toHex(bigIntToBytes(value, length));
}

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
    cout << "rsa" << endl;

    RsaKey key = generateKey(1024);
    cout << "key size: 1024 bits" << endl;
    cout << "n: " << toHex(key.n, 128) << endl;
    cout << "e: " << key.e << endl;
    cout << "d: " << toHex(key.d, 128) << endl;

    BigInt message = 123456789;
    BigInt ciphertext = encrypt(message, key);
    BigInt decrypted = decrypt(ciphertext, key);
    cout << "message: " << message << endl;
    cout << "ciphertext: " << toHex(ciphertext, 128) << endl;
    cout << "decrypted: " << decrypted << endl;

    string text = "hello rsa";
    BigInt signature = signMessage(text, key);
    cout << "signed text: " << text << endl;
    cout << "sha256: " << toHex(sha256(toBytes(text))) << endl;
    cout << "signature: " << toHex(signature, 128) << endl;
    cout << "verify: " << (verifySignature(text, signature, key) ? "true" : "false") << endl;

    RsaKey small;
    small.n = 61 * 53;
    small.e = 17;
    small.d = modinv(small.e, 60 * 52);
    check("small example p=61 q=53",
          small.n == 3233 && small.d == 2753 && encrypt(65, small) == 2790 && decrypt(2790, small) == 65);
    check("roundtrip 1024 bit", decrypted == message);
    check("sign/verify", verifySignature(text, signature, key));

    return failed ? 1 : 0;
}
