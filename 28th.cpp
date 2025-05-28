#include <stdio.h>
#include <math.h>

// Modular exponentiation: (base^exp) % mod
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Publicly agreed values
    int q = 23;   // large prime modulus
    int a = 5;    // primitive root modulo q

    // Alice's secret
    int x = 6;
    int A = mod_exp(a, x, q);

    // Bob's secret
    int y = 15;
    int B = mod_exp(a, y, q);

    // Shared key computation
    int key_Alice = mod_exp(B, x, q); // (a^y)^x mod q
    int key_Bob   = mod_exp(A, y, q); // (a^x)^y mod q

    printf("Public: q = %d, a = %d\n", q, a);
    printf("Alice sends: %d\n", A);
    printf("Bob sends:   %d\n", B);
    printf("Shared key (Alice): %d\n", key_Alice);
    printf("Shared key (Bob):   %d\n", key_Bob);

    return 0;
}
