#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2
#define MOD 26

// Function to get modulo inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to get determinant of 2x2 matrix
int determinant(int key[SIZE][SIZE]) {
    return (key[0][0]*key[1][1] - key[0][1]*key[1][0]) % MOD;
}

// Function to find inverse key matrix
int findInverseKey(int key[SIZE][SIZE], int invKey[SIZE][SIZE]) {
    int det = determinant(key);
    if (det < 0)
        det += MOD;
    int detInv = modInverse(det, MOD);
    if (detInv == -1)
        return 0; // Not invertible

    invKey[0][0] =  key[1][1] * detInv % MOD;
    invKey[0][1] = -key[0][1] * detInv % MOD;
    invKey[1][0] = -key[1][0] * detInv % MOD;
    invKey[1][1] =  key[0][0] * detInv % MOD;

    // Make all elements positive
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            invKey[i][j] = (invKey[i][j] + MOD) % MOD;
        }

    return 1;
}

// Convert char to int (A=0, B=1, ..., Z=25)
int charToInt(char c) {
    return toupper(c) - 'A';
}

// Convert int to char
char intToChar(int n) {
    return (n % 26) + 'A';
}

// Encrypt 2-letter block
void encryptBlock(int key[SIZE][SIZE], char* block, char* result) {
    for (int i = 0; i < SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += key[i][j] * charToInt(block[j]);
        }
        result[i] = intToChar(sum % MOD);
    }
}

// Decrypt 2-letter block
void decryptBlock(int invKey[SIZE][SIZE], char* block, char* result) {
    for (int i = 0; i < SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += invKey[i][j] * charToInt(block[j]);
        }
        result[i] = intToChar(sum % MOD);
    }
}

// Main function
int main() {
    int key[SIZE][SIZE] = {
        {3, 3},
        {2, 5}
    };

    int invKey[SIZE][SIZE];
    if (!findInverseKey(key, invKey)) {
        printf("Key matrix is not invertible mod 26.\n");
        return 1;
    }

    char plaintext[100], ciphertext[100], decrypted[100];
    printf("Enter plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    int len = strlen(plaintext);
    if (len % 2 != 0) {
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
        len++;
    }

    for (int i = 0; i < len; i += 2) {
        encryptBlock(key, &plaintext[i], &ciphertext[i]);
    }
    ciphertext[len] = '\0';

    printf("Encrypted: %s\n", ciphertext);

    for (int i = 0; i < len; i += 2) {
        decryptBlock(invKey, &ciphertext[i], &decrypted[i]);
    }
    decrypted[len] = '\0';

    printf("Decrypted: %s\n", decrypted);

    return 0;
}
