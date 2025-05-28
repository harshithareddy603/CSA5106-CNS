#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find modular inverse of a with respect to 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Encrypt function
void encrypt(char *plaintext, int a, int b) {
    printf("Encrypted Text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char p = toupper(plaintext[i]) - 'A';
            char c = (a * p + b) % 26 + 'A';
            printf("%c", c);
        } else {
            printf("%c", plaintext[i]); // Non-alphabetic characters are not encrypted
        }
    }
    printf("\n");
}

// Decrypt function
void decrypt(char *ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: 'a' and 26 are not coprime. Decryption impossible.\n");
        return;
    }
    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char c = toupper(ciphertext[i]) - 'A';
            char p = (a_inv * (c - b + 26)) % 26 + 'A';
            printf("%c", p);
        } else {
            printf("%c", ciphertext[i]); // Non-alphabetic characters are not decrypted
        }
    }
    printf("\n");
}

// Function to check if 'a' is coprime with 26
int isCoprime(int a, int m) {
    while (m != 0) {
        int temp = m;
        m = a % m;
        a = temp;
    }
    return a == 1; // True if gcd(a, 26) = 1
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    // Get plaintext and keys from user
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter value of 'a': ");
    scanf("%d", &a);
    printf("Enter value of 'b': ");
    scanf("%d", &b);

    // Check if 'a' is coprime with 26
    if (!isCoprime(a, 26)) {
        printf("Error: 'a' must be coprime with 26. Choose a valid 'a'.\n");
        return 1;
    }

    // Encrypt the message
    encrypt(plaintext, a, b);

    // Get ciphertext from user for decryption
    printf("Enter ciphertext for decryption: ");
    scanf("%s", ciphertext);

    // Decrypt the message
    decrypt(ciphertext, a, b);

    return 0;
}
