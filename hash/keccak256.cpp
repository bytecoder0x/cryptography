#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/keccak256.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

string keccakHex(const string& message) {
    return toHex(keccak256(toBytes(message)));
}

int main() {
    string message = "hello";
    cout << "keccak256" << endl;
    cout << "message: " << message << endl;
    cout << "hash: " << keccakHex(message) << endl;
    cout << "sha3-256 of \"\" (padding 0x06): " << toHex(keccakSponge(Bytes(), 0x06)) << endl;

    check("empty string",
          keccakHex("") == "c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470");
    check("abc",
          keccakHex("abc") == "4e03657aea45a94fc7d47ba826c8d667c0d1e6e33a64a036ec44f58fa12d6c45");
    check("hello",
          keccakHex("hello") == "1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8");
    check("sha3-256 of empty string is different",
          toHex(keccakSponge(Bytes(), 0x06)) == "a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a");

    return failed ? 1 : 0;
}
