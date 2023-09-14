#include <iostream>

#include "common/bigint.h"
#include "common/prime.h"

using namespace std;

int bitLength(BigInt n) {
    int bits = 0;

    while (n > 0) {
        n >>= 1;
        bits++;
    }

    return bits;
}

int main() {
    cout << "miller-rabin primality test" << endl;

    BigInt mersenne61 = (BigInt(1) << 61) - 1;
    BigInt mersenne127 = (BigInt(1) << 127) - 1;
    BigInt carmichael561 = 561;
    BigInt carmichael1105 = 1105;
    BigInt fermat6 = (BigInt(1) << 64) + 1;

    cout << "2^61-1: " << mersenne61 << endl;
    cout << "is prime: " << (isProbablePrime(mersenne61) ? "true" : "false") << endl;
    cout << "2^127-1: " << mersenne127 << endl;
    cout << "is prime: " << (isProbablePrime(mersenne127) ? "true" : "false") << endl;
    cout << "561: " << carmichael561 << endl;
    cout << "is prime: " << (isProbablePrime(carmichael561) ? "true" : "false") << endl;
    cout << "1105: " << carmichael1105 << endl;
    cout << "is prime: " << (isProbablePrime(carmichael1105) ? "true" : "false") << endl;
    cout << "2^64+1: " << fermat6 << endl;
    cout << "is prime: " << (isProbablePrime(fermat6) ? "true" : "false") << endl;

    BigInt prime256 = randomPrime(256);
    cout << "randomPrime(256): " << prime256 << endl;
    cout << "bit length: " << bitLength(prime256) << endl;

    bool failed = false;

    bool ok1 = isProbablePrime(mersenne61);
    cout << "check 2^61-1 is prime: " << (ok1 ? "OK" : "FAIL") << endl;

    if (!ok1) {
        failed = true;
    }

    bool ok2 = isProbablePrime(mersenne127);
    cout << "check 2^127-1 is prime: " << (ok2 ? "OK" : "FAIL") << endl;

    if (!ok2) {
        failed = true;
    }

    bool ok3 = !isProbablePrime(carmichael561);
    cout << "check 561 is composite: " << (ok3 ? "OK" : "FAIL") << endl;

    if (!ok3) {
        failed = true;
    }

    bool ok4 = !isProbablePrime(carmichael1105);
    cout << "check 1105 is composite: " << (ok4 ? "OK" : "FAIL") << endl;

    if (!ok4) {
        failed = true;
    }

    // 2^64+1 = 274177 * 67280421310721
    BigInt factor1 = 274177;
    BigInt factor2 = BigInt("67280421310721");
    bool ok5 = !isProbablePrime(fermat6) && (factor1 * factor2 == fermat6);
    cout << "check 2^64+1 is composite: " << (ok5 ? "OK" : "FAIL") << endl;

    if (!ok5) {
        failed = true;
    }

    bool ok6 = (bitLength(prime256) == 256) && isProbablePrime(prime256);
    cout << "check random 256 bit prime: " << (ok6 ? "OK" : "FAIL") << endl;

    if (!ok6) {
        failed = true;
    }

    return failed ? 1 : 0;
}
