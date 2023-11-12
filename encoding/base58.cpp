#include <iostream>

#include "common/hex.h"
#include "encoding/base58.h"

using namespace std;

int main() {
    Bytes input = toBytes("hello world");
    string encoded = base58Encode(input);

    cout << "input: hello world" << endl;
    cout << "encoded: " << encoded << endl;

    return 0;
}
