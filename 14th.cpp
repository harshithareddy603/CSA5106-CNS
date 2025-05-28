#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char *p, int *k, char *c) {
    for (int i = 0; p[i]; i++)
        c[i] = (p[i] >= 'a' && p[i] <= 'z') ? ((p[i] - 'a' + k[i]) % ALPHABET_SIZE) + 'a' : p[i];
}

int main() {
    char p[] = "send more money", c[50];
    int k[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    encrypt(p, k, c);
    printf("Ciphertext: %s\n", c);
    return 0;
}