#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key) {
    int n = strlen(plaintext), m = strlen(key), j = 0;
    printf("Encrypted Text: ");
    for (int i = 0; i < n; i++) {
        char p = toupper(plaintext[i]);
        if (isalpha(p)) {
            char k = toupper(key[j % m]) - 'A';
            char c = ((p - 'A') + k) % 26 + 'A';
            printf("%c", c);
            j++;
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

int main() {
    char plaintext[100], key[100];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline characters
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encrypt(plaintext, key);
    return 0;
}
