#include <iostream>
#include <string>
#include <vector>

#include "common/hex.h"
#include "hash/keccak256.h"
#include "hash/merkle.h"

using namespace std;

bool failed = false;

void check(const string& name, bool ok) {
    cout << "check " << name << ": " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }
}

// leaf is keccak256 of the 20 address bytes, like in solidity
Bytes addressLeaf(const string& address) {
    return keccak256(fromHex(address));
}

int main() {
    vector<string> allowlist = {
        "0xf39Fd6e51aad88F6F4ce6aB8827279cffFb92266",
        "0x70997970C51812dc3A010C7d01b50e0d17dc79C8",
        "0x3C44CdDdB6a900fa2b585dd299e03d12FA4293BC",
        "0x90F79bf6EB2c4f870365E785982E1f101E93b906",
        "0x15d34AAf54267DB7D7c367839AAf71A00a2C6A65"
    };

    vector<Bytes> leaves;

    for (size_t i = 0; i < allowlist.size(); i++) {
        leaves.push_back(addressLeaf(allowlist[i]));
    }
    MerkleTree tree(leaves);

    cout << "merkle tree" << endl;

    for (size_t i = 0; i < allowlist.size(); i++) {
        cout << "address " << i << ": " << allowlist[i] << endl;
    }
    cout << "root: " << toHex(tree.root()) << endl;

    size_t index = 3;
    vector<Bytes> proof = tree.proof(index);
    cout << "leaf " << index << ": " << toHex(leaves[index]) << endl;

    for (size_t i = 0; i < proof.size(); i++) {
        cout << "proof " << i << ": " << toHex(proof[i]) << endl;
    }

    check("proof for address 3", MerkleTree::verify(leaves[index], proof, tree.root()));
    Bytes wrongLeaf = addressLeaf("0x9965507D1a55bcC2695C58ba16FB37d819B0A4dc");
    check("wrong address", !MerkleTree::verify(wrongLeaf, proof, tree.root()));

    return failed ? 1 : 0;
}
