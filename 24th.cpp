#include <stdio.h>
#include <math.h>

// Function to compute gcd and multiplicative inverse
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

// Function to compute modular inverse
int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_gcd(e, phi, &x, &y);
    if (g != 1) return -1; // Inverse doesn't exist
    else return (x % phi + phi) % phi;
}

// Modular exponentiation (base^exp mod mod)
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Given
    int e = 31;
    int n = 3599;
    int p = 59, q = 61;
    int phi = (p - 1) * (q - 1);

    // Find private key d
    int d = mod_inverse(e, phi);
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Example: Encrypt and Decrypt a message
    int message = 123;
    int encrypted = mod_exp(message, e, n);
    int decrypted = mod_exp(encrypted, d, n);

    printf("Original Message: %d\n", message);
    printf("Encrypted Message: %d\n", encrypted);
    printf("Decrypted Message: %d\n", decrypted);

    return 0;
}