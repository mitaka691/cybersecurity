#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256
#define NUM_TESTS 100000
#define KEY_LEN 16


unsigned char rc4_get_byte(unsigned char *key, int key_len, int target_index) {
    unsigned char S[N];
    int i, j = 0;

    // KSA
    for (i = 0; i < N; i++)
        S[i] = i;

    for (i = 0; i < N; i++) {
        j = (j + S[i] + key[i % key_len]) % N;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    // PRGA
    i = 0;
    j = 0;

    for (int k = 0; k <= target_index; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        int t = (S[i] + S[j]) % N;

        if (k == target_index)
            return S[t];
    }

    return EXIT_SUCCESS; 
}

int main() {
    int count_zero = 0;
    unsigned char key[KEY_LEN];

    srand(time(NULL));

    for (int i = 0; i < NUM_TESTS; i++) {
        
        for (int j = 0; j < KEY_LEN; j++) {
            key[j] = rand() % 256;
        }

        // ??????? 2-??? ???? 
        unsigned char second_byte = rc4_get_byte(key, KEY_LEN, 1);

        if (second_byte == 0x00)
            count_zero++;
    }

    double probability = (double)count_zero / NUM_TESTS;

    printf("Total tests: %d\n", NUM_TESTS);
    printf("Zero count: %d\n", count_zero);
    printf("Probability: %.6f\n", probability);

    printf("Expected random: %.6f (1/256)\n", 1.0 / 256);
    printf("RC4 bias expected: %.6f (1/128)\n", 1.0 / 128);

    return EXIT_SUCCESS;
}