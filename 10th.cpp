#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

void find(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == ch) { *r = i; *c = j; return; }
}

void encrypt(const char *text, char *cipher) {
    char clean[512];
    int k = 0;

    for (int i = 0; text[i]; i++) {
        char c = toupper(text[i]);
        if (isalpha(c)) clean[k++] = (c == 'J') ? 'I' : c;
    }

    // Build digraphs
    char prepared[512];
    int j = 0;
    for (int i = 0; i < k; i++) {
        prepared[j++] = clean[i];
        if (i + 1 < k && clean[i] == clean[i + 1]) {
            prepared[j++] = 'X';
        }
    }
    if (j % 2 != 0) prepared[j++] = 'X';
    prepared[j] = '\0';

    // Encrypt
    for (int i = 0; i < j; i += 2) {
        int r1, c1, r2, c2;
        find(prepared[i], &r1, &c1);
        find(prepared[i+1], &r2, &c2);

        if (r1 == r2) {
            cipher[i]   = matrix[r1][(c1 + 1) % 5];
            cipher[i+1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher[i]   = matrix[(r1 + 1) % 5][c1];
            cipher[i+1] = matrix[(r2 + 1) % 5][c2];
        } else {
            cipher[i]   = matrix[r1][c2];
            cipher[i+1] = matrix[r2][c1];
        }
    }
    cipher[j] = '\0';
}

int main() {
    const char *message = "Must see you over Cadogan West. Coming at once.";
    char cipher[512];

    encrypt(message, cipher);
    printf("Encrypted Message:\n%s\n", cipher);

    return 0;
}
