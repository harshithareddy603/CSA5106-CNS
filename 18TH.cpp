#include <stdio.h>

void leftShift(unsigned int *halfKey, int shifts) {
    *halfKey = ((*halfKey << shifts) | (*halfKey >> (28 - shifts))) & 0xFFFFFFF;
}

void generateSubKeys(unsigned long long key, unsigned long long subkeys[16]) {
    unsigned int C = (key >> 28) & 0xFFFFFFF, D = key & 0xFFFFFFF;
    int shifts[16] = {1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1};
    
    for (int i = 0; i < 16; i++) {
        leftShift(&C, shifts[i]);
        leftShift(&D, shifts[i]);
        subkeys[i] = ((C >> 4) & 0xFFFFFF) | ((D >> 4) & 0xFFFFFF000000);
    }
}

void displaySubKeys(unsigned long long subkeys[16]) {
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: %llx\n", i + 1, subkeys[i]);
    }
}

int main() {
    unsigned long long key = 0x133457799BBCDFF1;
    unsigned long long subkeys[16];
    generateSubKeys(key, subkeys);
    displaySubKeys(subkeys);
    return 0;
}