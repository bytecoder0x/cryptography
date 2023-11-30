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

## Build and run

C++17, CMake 3.26+ and Boost headers (only multiprecision is used).

```
cmake -B build
cmake --build build
./build/sha256
```

Or one file directly:

```
g++ -std=c++17 -I. hash/sha256.cpp -o sha256
```

## Example

```
$ ./build/ecdsa
ecdsa secp256k1
public key x: 1d46f450469d43a49fb197072b01278d887dd4361315ab4b590ba408d676fca0
public key y: fd58a9ac778a8c65688bbac20e2ea09f93aafa31a3acc1b21e916a14b56c506c
address: 0xe2752bec23ae1d1553768ee2779c93270b00532b
message: hello
keccak256: 1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8
r: acd591bef94463d7bbf73327b15dce00e8a7731cd07f05dbdbc6e55727d80be3
s: 4325735102bdb313dc60caca3c10e5937697b0b9b900800e673f157a5a304cc8
v: 28
verify: true
recovered address: 0xe2752bec23ae1d1553768ee2779c93270b00532b
check key 1 is the generator: OK
check address of key 1: OK
check address of key 2: OK
check verify: OK
check recover address: OK
```

The private key is printed first, I removed it from the example. Signature is different every run because k is random.
