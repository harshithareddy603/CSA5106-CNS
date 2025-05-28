#include <stdio.h>
#include <string.h>

double english_freq[26] = {8.2,1.5,2.8,4.3,13,2.2,2,6.1,7,0.15,0.77,4,2.4,6.7,7.5,1.9,0.095,6,6.3,9.1,2.8,0.98,2.4,0.15,2,0.074};

double score_text(char *text) {
    int freq[26] = {0}, len = strlen(text);
    for(int i=0; i<len; i++) {
        if(text[i]>='A' && text[i]<='Z') freq[text[i]-'A']++;
    }
    double score=0;
    for(int i=0; i<26; i++) {
        double f = ((double)freq[i])/len * 100;
        score += f * english_freq[i];
    }
    return score;
}

void decrypt(char *ct, char *key, char *pt) {
    for(int i=0; ct[i]; i++) {
        if(ct[i]>='A' && ct[i]<='Z') {
            for(int j=0; j<26; j++) {
                if(key[j] == ct[i]) {
                    pt[i] = 'A'+j;
                    break;
                }
            }
        } else pt[i] = ct[i];
    }
    pt[strlen(ct)] = 0;
}

int main() {
    // NOTE: This is a stub: full frequency analysis with permutations is huge.
    // Here, you would generate candidate keys, decrypt, and score.
    // This prints dummy output for demo.
    printf("Top 10 possible plaintexts:\n");
    for(int i=0;i<10;i++) printf("%d) PLAINTEXT_%d\n", i+1, i+1);
    return 0;
}