#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simple XOR function for blocks
void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *out, int len) {
    for(int i=0; i<len; i++) out[i] = a[i] ^ b[i];
}

// Simple "block cipher" encrypt function (for demo)
void block_encrypt(uint8_t *key, uint8_t *in, uint8_t *out, int len) {
    for(int i=0; i<len; i++) out[i] = in[i] ^ key[i]; // XOR with key
}

// CBC-MAC for one block message X
void CBC_MAC(uint8_t *key, uint8_t *X, int len, uint8_t *T) {
    block_encrypt(key, X, T, len);
}

int main() {
    uint8_t key[16] = {0x1};  // Example key
    uint8_t X[16] = {0xA};    // Example one-block message
    uint8_t T[16];
    
    CBC_MAC(key, X, 16, T);
    
    printf("CBC-MAC of one-block message T = ");
    for(int i=0; i<16; i++) printf("%02X", T[i]);
    printf("\n");

    // Compute X ? T
    uint8_t X_xor_T[16];
    xor_blocks(X, T, X_xor_T, 16);

    // Now adversary knows CBC-MAC for X || (X ? T)
    // Compute CBC-MAC for 2-block message: CBC-MAC is CBC encrypt chain
    uint8_t intermediate[16];
    block_encrypt(key, X, intermediate, 16); // first block
    uint8_t second_block_input[16];
    xor_blocks(X_xor_T, intermediate, second_block_input, 16);
    uint8_t T2[16];
    block_encrypt(key, second_block_input, T2, 16);

    printf("CBC-MAC for two-block message X||(X?T) = ");
    for(int i=0; i<16; i++) printf("%02X", T2[i]);
    printf("\n");

    return 0;
}
