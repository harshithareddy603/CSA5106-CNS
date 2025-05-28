#include <stdio.h>
#include <ctype.h>

int main() {
    char key[27], plain[100], cipher[100];
    int i;
    printf("Key (26 letters): ");
    fgets(key, 27, stdin);
    getchar(); 
    printf("Plaintext: ");
    fgets(plain, 100, stdin);

    for (i = 0; plain[i] && plain[i] != '\n'; i++) {
        if (isupper(plain[i]))
            cipher[i] = toupper(key[plain[i] - 'A']);
        else if (islower(plain[i]))
            cipher[i] = tolower(key[plain[i] - 'a']);
        else
            cipher[i] = plain[i];
    }
    cipher[i] = '\0';
    printf("Ciphertext: %s\n", cipher);
    return 0;
}
