#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to build cipher alphabet from keyword
void build_cipher_alphabet(const char *keyword, char cipher_alphabet[26]) {
    int used[26] = {0}; // Tracks used letters
    int index = 0;

    // Add keyword to cipher alphabet
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = toupper(keyword[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            cipher_alphabet[index++] = c;
            used[c - 'A'] = 1;
        }
    }

    // Add remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher_alphabet[index++] = c;
        }
    }
}

// Function to encrypt using the generated cipher alphabet
void encrypt(const char *plaintext, const char cipher_alphabet[26], char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            int pos = toupper(c) - 'A';
            char enc = cipher_alphabet[pos];
            ciphertext[i] = isupper(c) ? enc : tolower(enc);
        } else {
            ciphertext[i] = c;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    const char keyword[] = "CIPHER";
    const char plaintext[] = "we are discovered run at once";
    char cipher_alphabet[26];
    char ciphertext[256];

    build_cipher_alphabet(keyword, cipher_alphabet);

    printf("Generated cipher alphabet:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c ", cipher_alphabet[i]);
    }
    printf("\n");

    encrypt(plaintext, cipher_alphabet, ciphertext);
    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
