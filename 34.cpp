#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simple XOR "encryption" as block cipher placeholder (normally use AES)
void block_encrypt(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < 8; i++) block[i] ^= key[i];
}
void block_decrypt(uint8_t *block, uint8_t *key) {
    block_encrypt(block, key); // XOR symmetric
}

// Padding: always add at least one block of padding
int pad(uint8_t *data, int len, int blocksize) {
    int pad_len = blocksize - (len % blocksize);
    if (pad_len == 0) pad_len = blocksize; // always pad
    data[len] = 0x80; // 10000000 binary
    for (int i = 1; i < pad_len; i++)
        data[len + i] = 0x00;
    return len + pad_len; // new length after padding
}

void ecb_encrypt(uint8_t *data, int len, uint8_t *key) {
    for (int i = 0; i < len; i += 8)
        block_encrypt(data + i, key);
}

void cbc_encrypt(uint8_t *data, int len, uint8_t *key, uint8_t *iv) {
    uint8_t prev[8];
    memcpy(prev, iv, 8);
    for (int i = 0; i < len; i += 8) {
        for (int j = 0; j < 8; j++) data[i + j] ^= prev[j];
        block_encrypt(data + i, key);
        memcpy(prev, data + i, 8);
    }
}

void cfb_encrypt(uint8_t *data, int len, uint8_t *key, uint8_t *iv) {
    uint8_t prev[8], temp[8];
    memcpy(prev, iv, 8);
    for (int i = 0; i < len; i += 8) {
        memcpy(temp, prev, 8);
        block_encrypt(temp, key);
        for (int j = 0; j < 8; j++) {
            data[i + j] ^= temp[j];
            prev[j] = data[i + j];
        }
    }
}

int main() {
    uint8_t key[8] = {1, 2, 3, 4, 5, 6, 7, 8}, iv[8] = {0};
    uint8_t data[32] = "HELLO WORLD!!!"; 
    int len = strlen((char *)data);

    len = pad(data, len, 8); // pad returns new length

    // Encrypt - you can choose ECB, CBC, or CFB here:
    ecb_encrypt(data, len, key);
    // cbc_encrypt(data, len, key, iv);
    // cfb_encrypt(data, len, key, iv);

    printf("Encrypted:");
    for (int i = 0; i < len; i++) printf(" %02X", data[i]);
    printf("\n");
    return 0;
}