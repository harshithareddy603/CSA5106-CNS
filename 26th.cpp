#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Compute GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Extended Euclidean Algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0; *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Modular inverse
int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_gcd(e, phi, &x, &y);
    if (g != 1) return -1;
    else return (x % phi + phi) % phi;
}

// Modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2) result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Step 1: Use small primes (for demo)
    int p = 53, q = 61;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Step 2: Choose e such that 1 < e < phi and gcd(e, phi) = 1
    int e = 17;
    if (gcd(e, phi) != 1) {
        printf("Invalid e, not coprime to phi.\n");
        return 1;
    }

    // Step 3: Compute d
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Failed to compute modular inverse.\n");
        return 1;
    }

    printf("Original Keys:\nPublic Key (e = %d, n = %d)\nPrivate Key (d = %d, n = %d)\n", e, n, d, n);

    // Message
    int message = 42;
    int cipher = mod_exp(message, e, n);
    int decrypted = mod_exp(cipher, d, n);
    printf("Encrypted: %d\nDecrypted: %d\n", cipher, decrypted);

    // Simulate key leak
    printf("\nPrivate key leaked! Bob tries to generate new keys with same modulus...\n");
    int e2 = 23;
    int d2 = mod_inverse(e2, phi);
    printf("New Public Key (e = %d), New Private Key (d = %d), using SAME n = %d\n", e2, d2, n);
    printf("But this is NOT SAFE because attacker can compute f(n) and factor n!\n");

    return 0;
}