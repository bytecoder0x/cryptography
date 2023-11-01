#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
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

    Point g = publicKey(1);
    cout << "1 * G: " << toHex(g.x, 32) << toHex(g.y, 32) << endl;
    return 0;
}
