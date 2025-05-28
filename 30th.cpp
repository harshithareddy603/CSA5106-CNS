#include <stdio.h>
#include <stdint.h>

// Simple XOR-based block cipher placeholder: encrypts 1 block using key
uint8_t simple_encrypt(uint8_t block, uint8_t key) {
    return block ^ key; // just XOR for demo; replace with AES or DES in real use
}

// Compute CBC-MAC of message M of length `len` blocks with key K
uint8_t cbc_mac(uint8_t *msg, int len, uint8_t key) {
    uint8_t iv = 0, out = iv;
    for (int i = 0; i < len; i++) {
        out = simple_encrypt(out ^ msg[i], key);
    }
    return out;
}

int main() {
    uint8_t key = 0xAA;           // symmetric key
    uint8_t X = 0x42;             // original 1-block message
    uint8_t T = cbc_mac(&X, 1, key);  // CBC-MAC of message X

    uint8_t forged[2] = {X, X ^ T};   // attacker forges message: X || (X ? T)
    uint8_t forged_mac = cbc_mac(forged, 2, key); // CBC-MAC of forged 2-block msg

    printf("Original message block X:    0x%02X\n", X);
    printf("CBC-MAC of X:                0x%02X\n", T);
    printf("Forged message:              0x%02X 0x%02X\n", forged[0], forged[1]);
    printf("CBC-MAC of forged message:   0x%02X\n", forged_mac);
    printf("Forgery successful? %s\n", forged_mac == T ? "YES" : "NO");

    return 0;
}
