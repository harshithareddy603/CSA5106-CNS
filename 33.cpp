#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void dsa_sign_demo(int message) {
    int p = 23, q = 11, g = 2;
    int x = 7; // private key
    int k = rand() % (q-1) + 1; // random k each time
    int r = mod_exp(g, k, p) % q;
    int s = ((message + x * r) * k) % q; // simplified
    printf("Message: %d, k: %d, Signature (r,s): (%d,%d)\n", message, k, r, s);
}

void rsa_sign_demo(int message) {
    int d = 7, n = 33; // private key (simplified)
    int signature = 1;
    for (int i = 0; i < d; i++) signature = (signature * message) % n;
    printf("Message: %d, RSA Signature: %d\n", message, signature);
}

int main() {
    srand(time(NULL));
    int message = 5;

    dsa_sign_demo(message);
    dsa_sign_demo(message);

    rsa_sign_demo(message);
    rsa_sign_demo(message);

    return 0;
}
