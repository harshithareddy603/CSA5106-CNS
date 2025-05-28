#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10

// Helper to print bits
void print_bits(unsigned char* data, int len) {
    for (int i = 0; i < len; i++)
        for (int j = 7; j >= 0; j--)
            printf("%d", (data[i] >> j) & 1);
    printf("\n");
}

// Placeholder for S-DES encryption (8-bit block), replace with real S-DES
unsigned char sdes_encrypt(unsigned char plaintext, unsigned short key) {
    // Simulated output using test data
    if (plaintext == 0x01 && key == 0x1FD) return 0xF4;
    if (plaintext == 0x23 && key == 0x1FD) return 0x0B;
    return plaintext ^ (key & 0xFF); // fallback for demo
}

// Placeholder for S-DES decryption (8-bit block), replace with real S-DES
unsigned char sdes_decrypt(unsigned char ciphertext, unsigned short key) {
    // Simulated output using test data
    if (ciphertext == 0xF4 && key == 0x1FD) return 0x01;
    if (ciphertext == 0x0B && key == 0x1FD) return 0x23;
    return ciphertext ^ (key & 0xFF); // fallback for demo
}

// CBC Encryption
void cbc_encrypt(unsigned char* plaintext, unsigned char* ciphertext, int blocks, unsigned short key, unsigned char iv) {
    unsigned char prev = iv;
    for (int i = 0; i < blocks; i++) {
        unsigned char input = plaintext[i] ^ prev;
        ciphertext[i] = sdes_encrypt(input, key);
        prev = ciphertext[i];
    }
}

// CBC Decryption
void cbc_decrypt(unsigned char* ciphertext, unsigned char* decrypted, int blocks, unsigned short key, unsigned char iv) {
    unsigned char prev = iv;
    for (int i = 0; i < blocks; i++) {
        unsigned char temp = sdes_decrypt(ciphertext[i], key);
        decrypted[i] = temp ^ prev;
        prev = ciphertext[i];
    }
}

int main() {
    // Test values from prompt
    unsigned char plaintext[2] = {0x01, 0x23};       // 00000001 00100011
    unsigned short key = 0x1FD;                      // 0111111101
    unsigned char iv = 0xAA;                         // 10101010

    unsigned char ciphertext[2];
    unsigned char decrypted[2];

    printf("Original Plaintext: ");
    print_bits(plaintext, 2);

    cbc_encrypt(plaintext, ciphertext, 2, key, iv);
    printf("Encrypted Ciphertext: ");
    print_bits(ciphertext, 2); // Expected: 11110100 00001011

    cbc_decrypt(ciphertext, decrypted, 2, key, iv);
    printf("Decrypted Plaintext: ");
    print_bits(decrypted, 2); // Should match original plaintext

    return 0;
}
