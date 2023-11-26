# cryptography

Algorithms from my cryptography course, written in C++ without crypto libraries (only Boost for big numbers).
Every file is a small demo that prints the result and checks it against known values.

## Algorithms

| Topic | File | What is inside |
|---|---|---|
| Classical | `classical/vigenere.cpp` | Vigenere cipher, encrypt and decrypt |
| Number theory | `number-theory/euclid.cpp` | gcd, extended Euclid, modular inverse |
| Number theory | `number-theory/miller-rabin.cpp` | Miller-Rabin primality test, random primes |
| Hash | `hash/sha256.h` | SHA-256 |
| Hash | `hash/keccak256.h` | Keccak-256, the one Ethereum uses (not SHA3-256) |
| Hash | `hash/hmac.h` | HMAC-SHA256 |
| Hash | `hash/merkle.h` | Merkle tree with proofs, sorted pairs like in OpenZeppelin |
| Public key | `public-key/rsa.cpp` | RSA key generation, encryption, signature |
| Public key | `public-key/diffie-hellman.cpp` | Diffie-Hellman key exchange |
| Public key | `public-key/ecdsa.h` | secp256k1, ECDSA sign and verify, recover, Ethereum address |
| Encoding | `encoding/base58.h` | base58 and base58check |

Shared stuff is in `common/`: `BigInt` (boost cpp_int), modular arithmetic, Miller-Rabin, random numbers, hex.
The `.h` is the algorithm, the `.cpp` with the same name is the demo.

## Build

```
cmake -B build
cmake --build build
```
