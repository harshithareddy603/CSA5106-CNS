#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Frequency of letters in English (approximate frequencies in %)
double english_freq[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};

// Function to calculate the frequency of each letter in the ciphertext
void calculate_frequency(const char *ciphertext, double freq[26]) {
    int length = strlen(ciphertext);
    for (int i = 0; i < 26; i++) {
        freq[i] = 0;  // Initialize frequencies to 0
    }
    for (int i = 0; i < length; i++) {
        char c = tolower(ciphertext[i]);
        if (isalpha(c)) {
            freq[c - 'a']++;
        }
    }
    // Convert to percentage
    for (int i = 0; i < 26; i++) {
        freq[i] = (freq[i] / length) * 100;
    }
}

// Function to sort frequencies in descending order
void sort_frequency(double freq[26], int order[26]) {
    double temp_freq;
    int temp_idx;
    
    // Simple bubble sort to sort frequencies and the corresponding letters
    for (int i = 0; i < 26; i++) {
        order[i] = i;
    }
    
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[order[i]] < freq[order[j]]) {
                temp_freq = freq[order[i]];
                order[i] = order[j];
                order[j] = temp_freq;
            }
        }
    }
}

// Function to substitute ciphertext based on letter frequency
void substitute(const char *ciphertext, const int order[26], char *plaintext) {
    int length = strlen(ciphertext);
    char letter_mapping[26] = {0};
    for (int i = 0; i < 26; i++) {
        letter_mapping[order[i]] = 'a' + i;
    }
    
    for (int i = 0; i < length; i++) {
        char c = tolower(ciphertext[i]);
        if (isalpha(c)) {
            plaintext[i] = letter_mapping[c - 'a'];
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabet characters stay the same
        }
    }
    plaintext[length] = '\0';
}

// Function to generate multiple candidates and display the top N
void generate_candidates(const char *ciphertext, int top_n) {
    double ciphertext_freq[26];
    int order[26];
    char plaintext[1000];  // Assuming ciphertext length is less than 1000 characters
    
    // Step 1: Calculate letter frequencies of the ciphertext
    calculate_frequency(ciphertext, ciphertext_freq);
    
    // Step 2: Sort the frequencies in descending order
    sort_frequency(ciphertext_freq, order);
    
    // Step 3: Try substitutions and print the top N candidates
    printf("Top %d possible plaintexts based on frequency attack:\n", top_n);
    
    for (int i = 0; i < top_n; i++) {
        // Step 4: Substitute based on the current frequency order
        substitute(ciphertext, order, plaintext);
        printf("Candidate %d: %s\n", i + 1, plaintext);
        
        // Modify the order for next candidate (e.g., cyclically shift the order)
        int temp = order[0];
        for (int j = 0; j < 25; j++) {
            order[j] = order[j + 1];
        }
        order[25] = temp;
    }
}

int main() {
    // Ciphertext input (change it as needed)
    char ciphertext[] = "RAKCHA";
    
    // Ask user for how many candidates to show
    int top_n;
    printf("Enter the number of top candidates to display: ");
    scanf("%d", &top_n);
    
    // Generate and display the top N plaintext candidates
    generate_candidates(ciphertext, top_n);
    
    return 0;
}
