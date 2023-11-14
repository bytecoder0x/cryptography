#include <iostream>

#include "common/hex.h"
#include "encoding/base58.h"

using namespace std;

int main() {
    Bytes input = toBytes("hello world");
    string encoded = base58Encode(input);

    cout << "input: hello world" << endl;
    cout << "encoded: " << encoded << endl;
    cout << "decoded: " << toHex(base58Decode(encoded)) << endl;

    Bytes payload = fromHex("00010966776006953d5567439e5e39f86a0d273bee");
    cout << "bitcoin address: " << base58Check(payload) << endl;

    return 0;
}
