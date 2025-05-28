#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void decryptAffine(char *ciphertext, int a, int b) {
    int a_inv = modInverse(a, ALPHABET_SIZE);
    if (a_inv == -1) {
        printf("Error: 'a' and 26 are not coprime. Decryption impossible.\n");
        return;
    }

    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char c = toupper(ciphertext[i]) - 'A';
            char p = (a_inv * (c - b + ALPHABET_SIZE)) % ALPHABET_SIZE + 'A';
            printf("%c", p);
        } else {
            printf("%c", ciphertext[i]); // Non-alphabetic characters are not decrypted
        }
    }
    printf("\n");
}

// Function to solve for 'a' and 'b' using the most frequent letters
void breakAffineCipher(char *ciphertext, char mostFreq, char secondFreq) {
    int a, b;
    int x1 = mostFreq - 'A';  // Most frequent letter (probably 'B' -> 'E')
    int x2 = secondFreq - 'A'; // Second frequent letter (probably 'U' -> 'T')
    int y1 = 'E' - 'A';  // Assume 'E' corresponds to the most frequent letter
    int y2 = 'T' - 'A';  // Assume 'T' corresponds to the second most frequent letter

    // Solve for 'a' and 'b'
    for (a = 0; a < ALPHABET_SIZE; a++) {
        if (modInverse(a, ALPHABET_SIZE) == -1) continue;
        for (b = 0; b < ALPHABET_SIZE; b++) {
            if ((a * x1 + b) % ALPHABET_SIZE == y1 && (a * x2 + b) % ALPHABET_SIZE == y2) {
                printf("Found a: %d, b: %d\n", a, b);
                decryptAffine(ciphertext, a, b);
                return;
            }
        }
    }
    printf("Failed to break the cipher.\n");
}

int main() {
    char ciphertext[] = "BUZLJCV QPUWCM";  // Example ciphertext, replace with actual ciphertext

    // Given the most frequent letter 'B' (likely 'E') and second most frequent letter 'U' (likely 'T')
    breakAffineCipher(ciphertext, 'B', 'U');

    return 0;
}
