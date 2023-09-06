#include <iostream>
#include <string>

using namespace std;

string vigenereEncrypt(const string& text, const string& key) {
    string result;
    size_t j = 0;

    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            int shift = key[j % key.size()] - 'A';
            result += static_cast<char>('A' + (c - 'A' + shift) % 26);
            j++;
        } else {
            result += c;
        }
    }

    return result;
}

string vigenereDecrypt(const string& text, const string& key) {
    string result;
    size_t j = 0;

    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            int shift = key[j % key.size()] - 'A';
            result += static_cast<char>('A' + (c - 'A' - shift + 26) % 26);
            j++;
        } else {
            result += c;
        }
    }

    return result;
}

int main() {
    cout << "vigenere cipher" << endl;

    string key = "SECRET";
    string plaintext = "MEET ME AT THE LIBRARY AFTER CLASS";
    string ciphertext = vigenereEncrypt(plaintext, key);
    string decrypted = vigenereDecrypt(ciphertext, key);

    cout << "key: " << key << endl;
    cout << "plaintext: " << plaintext << endl;
    cout << "ciphertext: " << ciphertext << endl;
    cout << "decrypted: " << decrypted << endl;

    bool failed = false;

    // example from wikipedia
    string wikiKey = "LEMON";
    string wikiPlain = "ATTACKATDAWN";
    string wikiCipher = "LXFOPVEFRNHR";
    string enc = vigenereEncrypt(wikiPlain, wikiKey);
    string dec = vigenereDecrypt(enc, wikiKey);
    bool ok = (enc == wikiCipher) && (dec == wikiPlain);
    cout << "check LEMON / ATTACKATDAWN: " << (ok ? "OK" : "FAIL") << endl;

    if (!ok) {
        failed = true;
    }

    return failed ? 1 : 0;
}
