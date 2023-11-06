#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
#include "hash/keccak256.h"
#include "public-key/ecdsa.h"

using namespace std;

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

int main() {
    cout << "ecdsa secp256k1" << endl;

    BigInt privateKey = generatePrivateKey();
    Point pub = publicKey(privateKey);
    Bytes address = ethereumAddress(pub);
    cout << "private key: " << toHex(privateKey, 32) << endl;
    cout << "public key x: " << toHex(pub.x, 32) << endl;
    cout << "public key y: " << toHex(pub.y, 32) << endl;
    cout << "address: 0x" << toHex(address) << endl;

    string message = "hello";
    Bytes hash = keccak256(toBytes(message));
    Signature sig = sign(hash, privateKey);
    Point recovered = recover(hash, sig);
    cout << "message: " << message << endl;
    cout << "keccak256: " << toHex(hash) << endl;
    cout << "r: " << toHex(sig.r, 32) << endl;
    cout << "s: " << toHex(sig.s, 32) << endl;
    cout << "v: " << sig.v << endl;
    cout << "verify: " << (verify(hash, sig, pub) ? "true" : "false") << endl;
    cout << "recovered address: 0x" << toHex(ethereumAddress(recovered)) << endl;

    Point g = publicKey(1);
    check("key 1 is the generator",
          toHex(g.x, 32) == "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" &&
          toHex(g.y, 32) == "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
    check("address of key 1",
          toHex(ethereumAddress(g)) == "7e5f4552091a69125d5dfcb7b8c2659029395bdf");
    check("address of key 2",
          toHex(ethereumAddress(publicKey(2))) == "2b5ad5c4795c026514f8317c7a215e218dccd6cf");
    check("verify", verify(hash, sig, pub));
    check("recover address", ethereumAddress(recovered) == address);

    return failed ? 1 : 0;
}
