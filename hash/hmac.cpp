#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/hmac.h"

using namespace std;

int main() {
    Bytes key = toBytes("Jefe");
    Bytes data = toBytes("what do ya want for nothing?");
    cout << "hmac-sha256(\"Jefe\", \"what do ya want for nothing?\") = " << toHex(hmacSha256(key, data)) << endl;
    return 0;
}
