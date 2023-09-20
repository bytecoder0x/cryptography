#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/sha256.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

string sha256Hex(const string& message) {
    return toHex(sha256(toBytes(message)));
}

int main() {
    string message = "abc";
    cout << "sha256" << endl;
    cout << "message: " << message << endl;
    cout << "hash: " << sha256Hex(message) << endl;

    // vectors from the nist examples
    check("abc",
          sha256Hex("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    check("empty string",
          sha256Hex("") == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    check("56 bytes",
          sha256Hex("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") ==
          "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    check("112 bytes, two blocks",
          sha256Hex("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
                    "ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu") ==
          "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");

    return failed ? 1 : 0;
}
