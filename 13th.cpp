#include <stdio.h>

int modInverse(int a) {
    a %= 26;
    for (int x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return -1;
}

void inverseMatrix(int m[2][2], int inv[2][2]) {
    int det = (m[0][0]*m[1][1] - m[0][1]*m[1][0]) % 26;
    if (det < 0) det += 26;
    int invDet = modInverse(det);
    inv[0][0] = ( m[1][1] * invDet) % 26;
    inv[0][1] = (-m[0][1] * invDet + 26) % 26;
    inv[1][0] = (-m[1][0] * invDet + 26) % 26;
    inv[1][1] = ( m[0][0] * invDet) % 26;
}

int main() {
    int P[2][2] = {{7, 11}, {8, 11}};    // HI, LL
    int C[2][2] = {{12, 10}, {5, 3}};    // MF, KD
    int P_inv[2][2], K[2][2] = {{0,0},{0,0}};

    inverseMatrix(P, P_inv);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                K[i][j] = (K[i][j] + C[i][k] * P_inv[k][j]) % 26;

    printf("Recovered Key:\n");
    for (int i = 0; i < 2; i++)
        printf("%2d %2d\n", K[i][0], K[i][1]);

    return 0;
}
