#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 64
#define HALF_BLOCK 32
#define NUM_ROUNDS 16
#define KEY_SIZE 64

// Shift schedule
int shift_schedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Sample permutation arrays (simplified for clarity)
int initial_permutation[BLOCK_SIZE] = {
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4, 
    62, 54, 46, 38, 30, 22, 14, 6, 
    64, 56, 48, 40, 32, 24, 16, 8, 
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5, 
    63, 55, 47, 39, 31, 23, 15, 7
};

int final_permutation[BLOCK_SIZE] = {
    40, 8, 48, 16, 56, 24, 64, 32, 
    39, 7, 47, 15, 55, 23, 63, 31, 
    38, 6, 46, 14, 54, 22, 62, 30, 
    37, 5, 45, 13, 53, 21, 61, 29, 
    36, 4, 44, 12, 52, 20, 60, 28, 
    35, 3, 43, 11, 51, 19, 59, 27, 
    34, 2, 42, 10, 50, 18, 58, 26, 
    33, 1, 41, 9, 49, 17, 57, 25
};

void left_shift(int* key_half, int shift_count) {
    while (shift_count--) {
        int temp = key_half[0];
        for (int i = 0; i < 27; i++)
            key_half[i] = key_half[i + 1];
        key_half[27] = temp;
    }
}

void xor_bits(int* a, int* b, int* result, int len) {
    for (int i = 0; i < len; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void permute(int* in, int* out, int* table, int len) {
    for (int i = 0; i < len; i++)
        out[i] = in[table[i] - 1];
}

void string_to_bits(char* str, int* bits, int size) {
    for (int i = 0; i < size; i++)
        bits[i] = str[i] - '0';
}

void print_bits(int* bits, int size) {
    for (int i = 0; i < size; i++)
        printf("%d", bits[i]);
    printf("\n");
}

void generate_keys(int* main_key, int subkeys[16][48]) {
    int key56[56];
    int C[28], D[28], CD[56];

    for (int i = 0, j = 0; i < 64; i++) {
        if ((i + 1) % 8 != 0)
            key56[j++] = main_key[i];
    }

    for (int i = 0; i < 28; i++) {
        C[i] = key56[i];
        D[i] = key56[i + 28];
    }

    for (int round = 0; round < 16; round++) {
        left_shift(C, shift_schedule[round]);
        left_shift(D, shift_schedule[round]);
        for (int i = 0; i < 28; i++) {
            CD[i] = C[i];
            CD[i + 28] = D[i];
        }
        for (int i = 0; i < 48; i++)
            subkeys[round][i] = CD[i % 56];
    }
}

void feistel(int* R, int* subkey, int* out) {
    for (int i = 0; i < 32; i++)
        out[i] = R[i] ^ subkey[i % 48];
}

void des_decrypt(int* ciphertext, int* key, int* plaintext) {
    int IP[64], FP[64];
    int L[17][32], R[17][32], temp[64], f_out[32];
    int subkeys[16][48];

    generate_keys(key, subkeys);

    permute(ciphertext, IP, initial_permutation, 64);

    for (int i = 0; i < 32; i++) {
        L[0][i] = IP[i];
        R[0][i] = IP[i + 32];
    }

    for (int round = 1; round <= 16; round++) {
        for (int i = 0; i < 32; i++)
            L[round][i] = R[round - 1][i];

        feistel(R[round - 1], subkeys[16 - round], f_out);
        xor_bits(L[round - 1], f_out, R[round], 32);
    }

    for (int i = 0; i < 32; i++) {
        temp[i] = R[16][i];
        temp[i + 32] = L[16][i];
    }

    permute(temp, FP, final_permutation, 64);
    for (int i = 0; i < 64; i++)
        plaintext[i] = FP[i];
}

int main() {
    char key_str[65], cipher_str[65];
    int key[64], ciphertext[64], plaintext[64];

    printf("Enter 64-bit key (binary): ");
    scanf("%64s", key_str);
    printf("Enter 64-bit ciphertext (binary): ");
    scanf("%64s", cipher_str);

    string_to_bits(key_str, key, 64);
    string_to_bits(cipher_str, ciphertext, 64);

    des_decrypt(ciphertext, key, plaintext);

    printf("Decrypted plaintext (binary): ");
    print_bits(plaintext, 64);

    return 0;
}
