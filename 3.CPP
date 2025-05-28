#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

void generateMatrix(char *key) {
    int used[26] = {0}, x = 0, y = 0;
    for (int i = 0; key[i]; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!isalpha(ch) || used[ch - 'A']) continue;
        matrix[x][y++] = ch;
        used[ch - 'A'] = 1;
        if (y == SIZE) { x++; y = 0; }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J' || used[ch - 'A']) continue;
        matrix[x][y++] = ch;
        if (y == SIZE) { x++; y = 0; }
    }
}

void findPos(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (matrix[i][j] == ch) { *row = i; *col = j; return; }
}

void encrypt(char *text) {
    for (int i = 0; text[i]; i += 2) {
        char a = toupper(text[i]), b = toupper(text[i+1]);
        if (a == b) b = 'X';  // Padding
        int r1, c1, r2, c2;
        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);
        if (r1 == r2)
            printf("%c%c", matrix[r1][(c1+1)%SIZE], matrix[r2][(c2+1)%SIZE]);
        else if (c1 == c2)
            printf("%c%c", matrix[(r1+1)%SIZE][c1], matrix[(r2+1)%SIZE][c2]);
        else
            printf("%c%c", matrix[r1][c2], matrix[r2][c1]);
    }
    printf("\n");
}

int main() {
    char key[] = "KEYWORD";
    char text[] = "HELLO";
    generateMatrix(key);
    printf("Encrypted Text: ");
    encrypt(text);
    return 0;
}
