#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 16  // 128 bits
#define Rb_128 0x87
#define Rb_64  0x1B

// Left shift a block by 1 bit, returning carry out bit
uint8_t left_shift_one_bit(uint8_t *input, uint8_t *output, int len) {
    uint8_t carry = 0, next_carry;
    for (int i = len-1; i >= 0; i--) {
        next_carry = (input[i] & 0x80) ? 1 : 0;
        output[i] = (input[i] << 1) | carry;
        carry = next_carry;
    }
    return carry;
}

void generate_subkeys(uint8_t *L, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t Rb = (block_size == 8) ? Rb_64 : Rb_128;

    uint8_t carry = left_shift_one_bit(L, K1, block_size);
    if (carry) K1[block_size-1] ^= Rb;

    carry = left_shift_one_bit(K1, K2, block_size);
    if (carry) K2[block_size-1] ^= Rb;
}

int main() {
    uint8_t L[BLOCK_SIZE] = {0}; // should be output of block cipher of 0 block
    L[BLOCK_SIZE-1] = 0x80; // example value for demo

    uint8_t K1[BLOCK_SIZE], K2[BLOCK_SIZE];

    generate_subkeys(L, K1, K2, BLOCK_SIZE);

    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X", K1[i]);
    printf("\nK2: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X", K2[i]);
    printf("\n");

    return 0;
}
