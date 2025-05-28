#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to build reverse (decryption) key
void build_decryption_key(const char *key, char *decrypt_key) {
    for (int i = 0; i < 26; i++) {
        // Map encrypted character back to original character
        decrypt_key[toupper(key[i]) - 'A'] = 'A' + i;
    }
}

// Function to decrypt the ciphertext
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    char decrypt_key[26];
    build_decryption_key(key, decrypt_key);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isupper(c)) {
            plaintext[i] = decrypt_key[c - 'A'];
        } else if (islower(c)) {
            plaintext[i] = tolower(decrypt_key[toupper(c) - 'A']);
        } else {
            plaintext[i] = c; // Non-alphabet characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    // Substitution key (must be 26 unique uppercase letters)
    const char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    // Ciphertext to decrypt
    const char ciphertext[] = "Bpm ycqks jzwev bpm ugdl!";
    char plaintext[256];

    decrypt(ciphertext, key, plaintext);

    printf("Decrypted message: %s\n", plaintext);

    return 0;
}
