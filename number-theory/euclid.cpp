#include <iostream>

#include "common/bigint.h"
#include "common/modular.h"

using namespace std;

int main() {
    BigInt a = 240;
    BigInt b = 46;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "gcd(a, b): " << gcd(a, b) << endl;
    cout << "modinv(3, 11): " << modinv(3, 11) << endl;

    return 0;
}
