#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m; m = a % m; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }

    if (x1 < 0) x1 += m0;
    return x1;
}

int main() {
    int n = 2;
    int e = 2;
    int M = 24;
    int C = 1664;

    int common_factor = gcd(M, n);

    if (common_factor > 1 && common_factor < n) {
        printf("Common factor found: %d\n", common_factor);

        int p = common_factor;
        int q = n / p;

        printf("p = %d, q = %d\n", p, q);

        int phi_n = (p - 1) * (q - 1);

        int d = mod_inverse(e, phi_n);

        printf("Private key d = %d\n", d);

        int decrypted_M = 1;
        for (int i = 0; i < d; i++) {
            decrypted_M = (decrypted_M * C) % n;
        }

        printf("Decrypted plaintext block: %d\n", decrypted_M);
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}