#include <stdio.h>
#include <stdint.h>

#define SIZE 5
#define NUM_RATE_LANES 9
#define NUM_CAPACITY_LANES 7

typedef uint64_t lane_t;

void evolve(lane_t state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            lane_t new_val = state[i][j];
            if (i > 0) new_val ^= state[i-1][j];
            if (i < SIZE-1) new_val ^= state[i+1][j];
            if (j > 0) new_val ^= state[i][j-1];
            if (j < SIZE-1) new_val ^= state[i][j+1];
            state[i][j] = new_val;
        }
}

int main() {
    lane_t state[SIZE][SIZE] = {0};
    for (int i = 0; i < NUM_RATE_LANES; i++) 
        state[i / SIZE][i % SIZE] = 1;

    int iterations = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < NUM_CAPACITY_LANES; i++) {
            if (state[i / SIZE][i % SIZE] == 0) {
                done = 0;
                break;
            }
        }
        if (done) break;

        evolve(state);
        iterations++;
    }

    printf("%d\n", iterations);
    return 0;
}