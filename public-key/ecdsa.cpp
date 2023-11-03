#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
#include "hash/keccak256.h"
#include "public-key/ecdsa.h"

using namespace std;

string toHex(const BigInt& value, size_t length) {
    return toHex(bigIntToBytes(value, length));
}

int main() {
    BigInt privateKey = generatePrivateKey();
    Point pub = publicKey(privateKey);
    cout << "private key: " << toHex(privateKey, 32) << endl;
    cout << "public key: " << toHex(pub.x, 32) << toHex(pub.y, 32) << endl;

    Bytes hash = keccak256(toBytes("hello"));
    Signature sig = sign(hash, privateKey);
    cout << "r: " << toHex(sig.r, 32) << endl;
    cout << "s: " << toHex(sig.s, 32) << endl;
    cout << "v: " << sig.v << endl;
    cout << "verify: " << verify(hash, sig, pub) << endl;
    return 0;
}
