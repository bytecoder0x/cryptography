#include <iostream>

#include "common/hex.h"
#include "common/random.h"
#include "encoding/base58.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

int main() {
    cout << "base58 encoding" << endl;

    Bytes helloBytes = toBytes("hello world");
    string helloEncoded = base58Encode(helloBytes);
    Bytes helloDecoded = base58Decode(helloEncoded);

    cout << "input: hello world" << endl;
    cout << "encoded: " << helloEncoded << endl;
    cout << "decoded: " << toHex(helloDecoded) << endl;

    Bytes addressPayload = fromHex("00010966776006953d5567439e5e39f86a0d273bee");
    string address = base58Check(addressPayload);
    cout << "bitcoin payload: " << toHex(addressPayload) << endl;
    cout << "bitcoin address: " << address << endl;

    Bytes solanaKey = bigIntToBytes(randomBits(256), 32);
    string solanaEncoded = base58Encode(solanaKey);
    Bytes solanaDecoded = base58Decode(solanaEncoded);

    cout << "solana key: " << toHex(solanaKey) << endl;
    cout << "solana key base58: " << solanaEncoded << endl;

    check("hello world", helloEncoded == "StV1DL6CwTryKyV" && helloDecoded == helloBytes);
    check("bitcoin address", address == "16UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM");
    check("solana key roundtrip", solanaDecoded == solanaKey);

    return failed ? 1 : 0;
}
