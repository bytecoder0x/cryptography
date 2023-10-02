#include <iostream>

#include "common/bigint.h"
#include "common/modular.h"
#include "common/prime.h"
#include "common/random.h"

using namespace std;

int main() {
    BigInt p = randomPrime(512);
    BigInt g = 2;
    BigInt a = randomBelow(p - 2) + 1;
    BigInt b = randomBelow(p - 2) + 1;
    BigInt alicePublic = modpow(g, a, p);
    BigInt bobPublic = modpow(g, b, p);

    cout << "p = " << p << endl;
    cout << "g = " << g << endl;
    cout << "A = " << alicePublic << endl;
    cout << "B = " << bobPublic << endl;
    cout << "alice secret = " << modpow(bobPublic, a, p) << endl;
    cout << "bob secret = " << modpow(alicePublic, b, p) << endl;
    return 0;
}
