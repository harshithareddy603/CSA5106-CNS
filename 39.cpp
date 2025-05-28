#include <stdio.h>
#include <string.h>

void freq_attack_additive(char *ciphertext, int topN) {
    int len = strlen(ciphertext);
    int freq[26] = {0};
    for(int i=0; i<len; i++) {
        if(ciphertext[i]>='A' && ciphertext[i]<='Z') freq[ciphertext[i]-'A']++;
    }
    // Assume 'E' is most frequent plaintext letter
    int max_freq_char = 0;
    for(int i=1; i<26; i++) if(freq[i]>freq[max_freq_char]) max_freq_char = i;

    printf("Top %d plaintext guesses:\n", topN);
    for(int shift=0; shift<topN; shift++) {
        int key = (max_freq_char - ('E' - 'A') - shift + 26) % 26;
        printf("Key guess %d: %d\nDecrypted text: ", shift+1, key);
        for(int i=0; i<len; i++) {
            if(ciphertext[i]>='A' && ciphertext[i]<='Z')
                printf("%c", ((ciphertext[i]-'A' - key + 26) % 26) + 'A');
            else
                printf("%c", ciphertext[i]);
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG"; // "HELLO WORLD" shifted by 3
    freq_attack_additive(ciphertext, 5);
    return 0;
}
