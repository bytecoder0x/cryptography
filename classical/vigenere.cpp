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

int main() {
    string key = "SECRET";
    string plaintext = "MEET ME AT THE LIBRARY AFTER CLASS";
    string ciphertext = vigenereEncrypt(plaintext, key);

    cout << "plaintext: " << plaintext << endl;
    cout << "ciphertext: " << ciphertext << endl;

    return 0;
}
