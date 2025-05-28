#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 64  // 64-bit block size
#define KEY_SIZE 64  // 64-bit key size

void xor_bits(int* a, int* b, int* result, int len) {
    for (int i = 0; i < len; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void print_bits(int* bits, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", bits[i]);
    }
    printf("\n");
}

void string_to_bits(char* str, int* bits, int size) {
    for (int i = 0; i < size; i++) {
        bits[i] = str[i] - '0';
    }
}

void bits_to_string(int* bits, char* str, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = bits[i] + '0';
    }
    str[size] = '\0';
}

// Simple XOR based block cipher (for demonstration purposes)
void block_cipher(int* block, int* key, int* result) {
    xor_bits(block, key, result, BLOCK_SIZE);
}

// ECB Mode of Operation (Electronic Codebook)
void ecb_encrypt(int* plaintext, int* key, int* ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block_cipher(plaintext + i * BLOCK_SIZE, key, ciphertext + i * BLOCK_SIZE);
    }
}

// CBC Mode of Operation (Cipher Block Chaining)
void cbc_encrypt(int* plaintext, int* key, int* iv, int* ciphertext, int num_blocks) {
    int previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE * sizeof(int));

    for (int i = 0; i < num_blocks; i++) {
        int xor_block[BLOCK_SIZE];
        xor_bits(plaintext + i * BLOCK_SIZE, previous_block, xor_block, BLOCK_SIZE);
        block_cipher(xor_block, key, ciphertext + i * BLOCK_SIZE);
        memcpy(previous_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE * sizeof(int));
    }
}

// CFB Mode of Operation (Cipher Feedback)
void cfb_encrypt(int* plaintext, int* key, int* iv, int* ciphertext, int num_blocks) {
    int feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE * sizeof(int));

    for (int i = 0; i < num_blocks; i++) {
        int cipher_output[BLOCK_SIZE];
        block_cipher(feedback, key, cipher_output);
        
        xor_bits(plaintext + i * BLOCK_SIZE, cipher_output, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);

        // Shift feedback register for next block
        for (int j = 0; j < BLOCK_SIZE - 1; j++) {
            feedback[j] = feedback[j + 1];
        }
        feedback[BLOCK_SIZE - 1] = ciphertext[i * BLOCK_SIZE];
    }
}

// Padding function to ensure the plaintext length is a multiple of BLOCK_SIZE
void pad_plaintext(int* plaintext, int* padded_plaintext, int len) {
    int num_blocks = (len + BLOCK_SIZE - 1) / BLOCK_SIZE; // Calculate number of blocks
    int padded_len = num_blocks * BLOCK_SIZE;

    // Copy original plaintext and pad the remaining bits with zeros
    memcpy(padded_plaintext, plaintext, len * sizeof(int));
    for (int i = len; i < padded_len; i++) {
        padded_plaintext[i] = 0;  // Padding with zeros
    }
}

int main() {
    char key_str[65], plaintext_str[129], ciphertext_str[129];
    int key[KEY_SIZE], plaintext[BLOCK_SIZE * 2], padded_plaintext[BLOCK_SIZE * 2], ciphertext[BLOCK_SIZE * 2];
    int iv[BLOCK_SIZE] = {0}; // Initialization vector for CBC and CFB (could be random in real cases)

    // Read the key and plaintext
    printf("Enter 64-bit key (binary): ");
    scanf("%64s", key_str);
    printf("Enter plaintext (binary, multiple of 64-bits): ");
    scanf("%128s", plaintext_str);

    string_to_bits(key_str, key, KEY_SIZE);
    string_to_bits(plaintext_str, plaintext, strlen(plaintext_str));

    // Padding the plaintext if needed
    pad_plaintext(plaintext, padded_plaintext, strlen(plaintext_str));

    // ECB Mode Encryption
    ecb_encrypt(padded_plaintext, key, ciphertext);
    printf("\nECB Encrypted: ");
    bits_to_string(ciphertext, ciphertext_str, BLOCK_SIZE * 2);
    printf("%s\n", ciphertext_str);

    // CBC Mode Encryption
    cbc_encrypt(padded_plaintext, key, iv, ciphertext, 2); // 2 blocks of data
    printf("CBC Encrypted: ");
    bits_to_string(ciphertext, ciphertext_str, BLOCK_SIZE * 2);
    printf("%s\n", ciphertext_str);

    // CFB Mode Encryption
    cfb_encrypt(padded_plaintext, key, iv, ciphertext, 2); // 2 blocks of data
    printf("CFB Encrypted: ");
    bits_to_string(ciphertext, ciphertext_str, BLOCK_SIZE * 2);
    printf("%s\n", ciphertext_str);

    return 0;
}
