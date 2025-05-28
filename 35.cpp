#include <stdio.h>
#include <ctype.h>

void encrypt(char *pt, int *key, char *ct, int len) {
    for(int i=0; i<len; i++) {
        int p = toupper(pt[i]) - 'A';
        int c = (p + key[i]) % 26;
        ct[i] = c + 'A';
    }
    ct[len] = 0;
}

int main() {
    char pt[] = "HELLOWORLD";
    int key[] = {3,19,5,7,12,1,4,15,9,2}; // random shifts
    char ct[sizeof(pt)];
    encrypt(pt, key, ct, 10);
    printf("Ciphertext: %s\n", ct);
    return 0;
}