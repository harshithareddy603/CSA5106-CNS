#include <stdio.h>

// Calculate modular inverse of a mod 26
int mod26_inv(int a) {
    for(int i=0; i<26; i++) {
        if ((a*i)%26 == 1) return i;
    }
    return -1;
}

// Calculate determinant mod 26
int det(int matrix[2][2]) {
    return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0] + 26*26) % 26;
}

// Inverse matrix mod 26
int inverse_matrix(int matrix[2][2], int inv[2][2]) {
    int determinant = det(matrix);
    int det_inv = mod26_inv(determinant);
    if (det_inv == -1) return 0; // no inverse

    inv[0][0] = ( matrix[1][1] * det_inv) % 26;
    inv[0][1] = (-matrix[0][1] * det_inv + 26) % 26;
    inv[1][0] = (-matrix[1][0] * det_inv + 26) % 26;
    inv[1][1] = ( matrix[0][0] * det_inv) % 26;
    return 1;
}

void known_plaintext_attack(int P[2][2], int C[2][2], int K[2][2]) {
    int P_inv[2][2];
    if(!inverse_matrix(P, P_inv)) {
        printf("Plaintext matrix not invertible.\n");
        return;
    }
    // K = C * P^-1 mod 26
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            K[i][j] = 0;
            for(int k=0; k<2; k++) {
                K[i][j] += C[i][k] * P_inv[k][j];
            }
            K[i][j] %= 26;
        }
    }
}

int main() {
    // Plaintext blocks: HELLO => HE LL (H=7,E=4,L=11)
    int P[2][2] = {{7, 4}, {11, 11}}; // 2 blocks, 2x2 matrix
    int C[2][2] = {{19, 7}, {24, 17}}; // ciphertext matrix

    int K[2][2];
    known_plaintext_attack(P, C, K);

    printf("Recovered key matrix K:\n");
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) printf("%d ", K[i][j]);
        printf("\n");
    }
    return 0;
}
