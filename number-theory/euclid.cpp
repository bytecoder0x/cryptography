#include <iostream>

#include "common/bigint.h"
#include "common/modular.h"

using namespace std;

int main() {
    cout << "extended euclidean algorithm" << endl;

    BigInt a = 240;
    BigInt b = 46;

    BigInt g = gcd(a, b);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "gcd(a, b): " << g << endl;

    BigInt x, y;
    BigInt g2 = egcd(a, b, x, y);
    cout << "egcd x: " << x << endl;
    cout << "egcd y: " << y << endl;
    cout << "a*x + b*y: " << (a * x + b * y) << endl;

    BigInt m1 = modinv(3, 11);
    cout << "modinv(3, 11): " << m1 << endl;

    BigInt m2 = modinv(6, 9);
    cout << "modinv(6, 9): " << m2 << endl;

    bool failed = false;

    bool ok1 = (g == 2);
    cout << "check gcd(240, 46) = 2: " << (ok1 ? "OK" : "FAIL") << endl;

    if (!ok1) {
        failed = true;
    }

    bool ok2 = (g2 == 2 && x == -9 && y == 47);
    cout << "check egcd(240, 46) x = -9, y = 47: " << (ok2 ? "OK" : "FAIL") << endl;

    if (!ok2) {
        failed = true;
    }

    bool ok3 = (m1 == 4);
    cout << "check modinv(3, 11) = 4: " << (ok3 ? "OK" : "FAIL") << endl;

    if (!ok3) {
        failed = true;
    }

    bool ok4 = (m2 == 0);
    cout << "check modinv(6, 9) has no inverse: " << (ok4 ? "OK" : "FAIL") << endl;

    if (!ok4) {
        failed = true;
    }

    return failed ? 1 : 0;
}
