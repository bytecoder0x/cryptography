#include <iostream>
#include <string>

#include "common/bigint.h"
#include "common/hex.h"
#include "common/modular.h"
#include "common/prime.h"
#include "common/random.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

string toHex(const BigInt& value, size_t length) {
    return toHex(bigIntToBytes(value, length));
}

int main() {
    cout << "diffie-hellman" << endl;

    // g = 2 is not always a generator of the whole group, for a demo it is fine
    BigInt p = randomPrime(512);
    BigInt g = 2;
    BigInt a = randomBelow(p - 2) + 1;
    BigInt b = randomBelow(p - 2) + 1;
    BigInt alicePublic = modpow(g, a, p);
    BigInt bobPublic = modpow(g, b, p);
    BigInt aliceSecret = modpow(bobPublic, a, p);
    BigInt bobSecret = modpow(alicePublic, b, p);

    cout << "p: " << toHex(p, 64) << endl;
    cout << "g: " << g << endl;
    cout << "alice private: " << toHex(a, 64) << endl;
    cout << "bob private: " << toHex(b, 64) << endl;
    cout << "alice public: " << toHex(alicePublic, 64) << endl;
    cout << "bob public: " << toHex(bobPublic, 64) << endl;
    cout << "alice secret: " << toHex(aliceSecret, 64) << endl;
    cout << "bob secret: " << toHex(bobSecret, 64) << endl;

    check("same secret on both sides", aliceSecret == bobSecret);
    check("small example p=23 g=5",
          modpow(5, 6, 23) == 8 && modpow(5, 15, 23) == 19 && modpow(19, 6, 23) == 2 && modpow(8, 15, 23) == 2);

    return failed ? 1 : 0;
}
