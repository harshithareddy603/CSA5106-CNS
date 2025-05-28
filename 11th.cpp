#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    int i;
    for ( i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 5; // The number of positions in the Playfair cipher matrix
    unsigned long long keys = factorial(n);
    
    printf("The number of possible keys for the Playfair cipher is approximately 2^%llu\n", keys);
    
    return 0;
}