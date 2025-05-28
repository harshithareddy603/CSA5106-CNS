#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16  // 128 bits

// Placeholder function for encryption (In real life, use a real encryption algorithm like AES)
void encrypt_block(unsigned char* block, unsigned char* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];  // Simple XOR-based encryption
    }
}

// Placeholder function for decryption (In real life, use a real decryption algorithm)
void decrypt_block(unsigned char* block, unsigned char* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];  // Simple XOR-based decryption
    }
}

// ECB encryption: Encrypts each block independently
void ecb_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encrypt_block(&plaintext[i], key);
        memcpy(&ciphertext[i], &plaintext[i], BLOCK_SIZE);
    }
}

// ECB decryption: Decrypts each block independently
void ecb_decrypt(unsigned char* ciphertext, unsigned char* plaintext, unsigned char* key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        decrypt_block(&ciphertext[i], key);
        memcpy(&plaintext[i], &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[] = "This is a test message to demonstrate ECB mode!";
    unsigned char ciphertext[64];
    unsigned char decryptedtext[64];
    unsigned char key[BLOCK_SIZE] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };
    
    int length = strlen((char*)plaintext);
    
    printf("Original plaintext: %s\n", plaintext);
    
    ecb_encrypt(plaintext, ciphertext, key, length);
    printf("Ciphertext after ECB encryption: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");
    
    ecb_decrypt(ciphertext, decryptedtext, key, length);
    printf("Decrypted text: %s\n", decryptedtext);
    
    return 0;
}