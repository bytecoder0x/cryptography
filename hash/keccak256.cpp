#include <iostream>
#include <string>

#include "common/hex.h"
#include "hash/keccak256.h"

using namespace std;

int main() {
    cout << "keccak256(\"\") = " << toHex(keccak256(toBytes(""))) << endl;
    cout << "keccak256(\"abc\") = " << toHex(keccak256(toBytes("abc"))) << endl;
    cout << "keccak256(\"hello\") = " << toHex(keccak256(toBytes("hello"))) << endl;
    return 0;
}
