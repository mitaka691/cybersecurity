#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define MAX_DIST 100
#define ALPHABET 26

// GCD
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int gcd_array(int arr[], int n) {
    if (n == 0) return 0;

    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }
    return result;
}

// normalizirane na teksta
void normalize_text(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}

// kasiski
int kasiski_analysis(const char *text) {

    int len = strlen(text);
    int distances[MAX_DIST];
    int dist_count = 0;

    printf("\n--- KASISKI ANALYSIS ---\n");

    for (int i = 0; i < len - 3; i++) {

        char trigram[4];
        strncpy(trigram, &text[i], 3);
        trigram[3] = '\0';

        for (int j = i + 1; j < len - 3; j++) {

            if (strncmp(trigram, &text[j], 3) == 0) {

                int distance = j - i;

                printf("Found \"%s\" at %d and %d -> distance %d\n",
                       trigram, i, j, distance);

                if (dist_count < MAX_DIST) {
                    distances[dist_count++] = distance;
                }
            }
        }
    }

    printf("\nDistances: ");
    for (int i = 0; i < dist_count; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    int key_length = gcd_array(distances, dist_count);

    printf("\nEstimated key length: %d\n", key_length);

    return key_length;
}

// histograma
void print_histogram(const char *text) {
    int freq[ALPHABET] = {0};

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            freq[text[i] - 'A']++;
        }
    }

    printf("\n--- HISTOGRAM ---\n");
    for (int i = 0; i < ALPHABET; i++) {
        printf("%c: %d\n", 'A' + i, freq[i]);
    }
}

// premestvane
int score_shift(int freq[ALPHABET], int shift) {

    // naj-chesti bukvi
    char expected[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    int score = 0;

    for (int i = 0; i < ALPHABET; i++) {
        int shifted_index = (i + shift) % ALPHABET;

        // tejest
        for (int j = 0; j < 6; j++) {
            if (shifted_index == (expected[j] - 'A')) {
                score += freq[i] * (6 - j);
            }
        }
    }

    return score;
}

int find_shift(int freq[ALPHABET]) {

    int best_shift = 0;
    int best_score = -1;

    for (int shift = 0; shift < ALPHABET; shift++) {

        int score = score_shift(freq, shift);

        if (score > best_score) {
            best_score = score;
            best_shift = shift;
        }
    }

    return best_shift;
}

// vuzstanovqvane na klioch
void recover_key(const char *text, int key_length, char *key) {

    int len = strlen(text);

    for (int i = 0; i < key_length; i++) {

        int freq[ALPHABET] = {0};
        int count = 0;

        // pravi kolona
        for (int j = i; j < len; j += key_length) {
            freq[text[j] - 'A']++;
            count++;
        }

        int shift = find_shift(freq);
        key[i] = 'A' + shift;
    }

    key[key_length] = '\0';
}

// dekriptirane
void decrypt_vigenere(const char *text, const char *key, char *output) {

    int key_len = strlen(key);

    for (int i = 0; text[i]; i++) {
        int c = text[i] - 'A';
        int k = key[i % key_len] - 'A';

        output[i] = ((c - k + 26) % 26) + 'A';
    }

    output[strlen(text)] = '\0';
}


int main() {

    char cipher[] =
        "Lfwki mjc lps iswk hj oglkmvguragk m kmxmamjc vxwuyl: Ggi isw al xa eycx mf km kbqbdc laef lfwki mjc guzugskec zg bwymoacfvmqk, yfw xtw mlaid oyq bw fg ksdi ul qg vsyhjavefwb laef lfwki mjc fh snnggnw pwdavmqfaaxw. Fzc xbvel kwmlav gk yed emjx huxdavyxl.";

    char text[MAX_TEXT];
    normalize_text(cipher, text);

    printf("Normalized text: %s\n", text);

    print_histogram(text);

    int key_length = kasiski_analysis(text);

    if (key_length <= 1) {
        printf("Failed to estimate key length.\n");
        return 0;
    }

    char key[100];
    recover_key(text, key_length, key);

    printf("\nRecovered key: %s\n", key);

    char decrypted[MAX_TEXT];
    decrypt_vigenere(text, key, decrypted);

    printf("\nDecrypted text: %s\n", decrypted);

    return 0;
}