#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keySquare[5][5];

void buildKey(const char *key) {
    int used[26] = {0}, k = 0;
    used['J' - 'A'] = 1; // Treat I/J as same

    for (int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) keySquare[k / 5][k % 5] = c, used[c - 'A'] = 1, k++;
    }
    for (char c = 'A'; c <= 'Z'; c++)
        if (!used[c - 'A']) keySquare[k / 5][k % 5] = c, used[c - 'A'] = 1, k++;
}

void find(char c, int *r, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (keySquare[i][j] == c) *r = i, *col = j;
}

void encrypt(const char *text, char *out) {
    char clean[256]; int k = 0;
    for (int i = 0; text[i]; i++) {
        char c = toupper(text[i]);
        if (isalpha(c)) clean[k++] = (c == 'J' ? 'I' : c);
    }
    if (k % 2) clean[k++] = 'X';
    clean[k] = '\0';

    for (int i = 0; i < k; i += 2) {
        if (clean[i] == clean[i+1]) clean[i+1] = 'X';
        int r1, c1, r2, c2;
        find(clean[i], &r1, &c1);
        find(clean[i+1], &r2, &c2);

        if (r1 == r2)
            out[i] = keySquare[r1][(c1 + 1) % 5],
            out[i+1] = keySquare[r2][(c2 + 1) % 5];
        else if (c1 == c2)
            out[i] = keySquare[(r1 + 1) % 5][c1],
            out[i+1] = keySquare[(r2 + 1) % 5][c2];
        else
            out[i] = keySquare[r1][c2],
            out[i+1] = keySquare[r2][c1];
    }
    out[k] = '\0';
}

int main() {
    char cipher[256];
    buildKey("MONARCHY");
    encrypt("PT BOAT SUNK", cipher);
    printf("Encrypted: %s\n", cipher);
    return 0;
}
