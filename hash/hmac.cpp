#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/hmac.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

int main() {
    string key = "Jefe";
    string data = "what do ya want for nothing?";
    cout << "hmac-sha256" << endl;
    cout << "key: " << key << endl;
    cout << "data: " << data << endl;
    cout << "mac: " << toHex(hmacSha256(toBytes(key), toBytes(data))) << endl;

    check("rfc case 1",
          toHex(hmacSha256(Bytes(20, 0x0b), toBytes("Hi There"))) ==
          "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7");
    check("rfc case 2",
          toHex(hmacSha256(toBytes("Jefe"), toBytes("what do ya want for nothing?"))) ==
          "5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843");
    check("rfc case 6, long key",
          toHex(hmacSha256(Bytes(131, 0xaa), toBytes("Test Using Larger Than Block-Size Key - Hash Key First"))) ==
          "60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54");

    return failed ? 1 : 0;
}
