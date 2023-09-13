#include <iostream>

#include "common/bigint.h"
#include "common/prime.h"

using namespace std;

int main() {
    BigInt n = 97;
    cout << "n: " << n << endl;
    cout << "is prime: " << (isProbablePrime(n) ? "true" : "false") << endl;

    BigInt p = randomPrime(64);
    cout << "random prime (64 bits): " << p << endl;

    return 0;
}
