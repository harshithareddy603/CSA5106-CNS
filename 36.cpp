#include <stdio.h>

int mod_inverse(int a, int m) {
    for(int x=1; x<m; x++) {
        if ((a*x) % m == 1) return x;
    }
    return -1; // no inverse
}

void affine_encrypt(char *plaintext, int a, int b, char *ciphertext) {
    for(int i=0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((a * (plaintext[i] - 'A') + b) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
}

void affine_decrypt(char *ciphertext, int a, int b, char *plaintext) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse for a=%d\n", a);
        return;
    }
    for(int i=0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int val = (a_inv * ((ciphertext[i] - 'A') - b + 26)) % 26;
            plaintext[i] = val + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}

int main() {
    char plaintext[] = "HELLO";
    char ciphertext[6];
    char decrypted[6];

    int a = 5, b = 8; // a must be coprime with 26

    affine_encrypt(plaintext, a, b, ciphertext);
    ciphertext[5] = '\0';

    affine_decrypt(ciphertext, a, b, decrypted);
    decrypted[5] = '\0';

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
