#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/sha256.h"

using namespace std;

int main() {
    cout << "sha256(\"abc\") = " << toHex(sha256(toBytes("abc"))) << endl;
    cout << "sha256(\"\") = " << toHex(sha256(toBytes(""))) << endl;
    cout << "sha256(\"hello world\") = " << toHex(sha256(toBytes("hello world"))) << endl;
    return 0;
}
