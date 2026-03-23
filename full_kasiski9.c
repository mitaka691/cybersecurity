#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 2000
#define MAX_DIST 200
#define ALPHABET 26

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

// normalizirane teksta
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

    printf("\n--- KASISKI ---\n");

    for (int i = 0; i < len - 3; i++) {

        char trigram[4];
        strncpy(trigram, &text[i], 3);
        trigram[3] = '\0';

        for (int j = i + 1; j < len - 3; j++) {

            if (strncmp(trigram, &text[j], 3) == 0) {

                int distance = j - i;

                printf("%s at %d & %d -> %d\n",
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

    printf("Estimated key length: %d\n", key_length);

    return key_length;
}

// histograma
void print_histogram(const char *text) {
    int freq[ALPHABET] = {0};

    for (int i = 0; text[i]; i++) {
        freq[text[i] - 'A']++;
    }

    printf("\n--- HISTOGRAM ---\n");
    for (int i = 0; i < ALPHABET; i++) {
        printf("%c: %d\n", 'A' + i, freq[i]);
    }
}

// ocenqvane sprqmo chestoti
int score_shift(int freq[ALPHABET], int shift) {

    char common[] = "ETAOINSHRDLC"; // top 12 letters
    int score = 0;

    for (int i = 0; i < ALPHABET; i++) {

        int shifted = (i - shift + ALPHABET) % ALPHABET;

        for (int j = 0; j < 12; j++) {
            if (shifted == (common[j] - 'A')) {
                score += freq[i] * (12 - j);
            }
        }
    }

    return score;
}

// ocenqva celiq tekst
int score_text(const char *text) {

    int score = 0;

    for (int i = 0; text[i]; i++) {
        if (text[i] == 'E') score += 5;
        else if (text[i] == 'T') score += 4;
        else if (text[i] == 'A') score += 3;
        else if (text[i] == 'O') score += 3;
        else if (text[i] == 'I') score += 2;
        else if (text[i] == 'N') score += 2;
        
        else if (text[i] == 'Z' || text[i] == 'Q' || text[i] == 'X')
            score -= 2;
    }
    
    //bigrami
    for (int i = 0; text[i + 1]; i++) {

        if ((text[i] == 'T' && text[i+1] == 'H') ||
            (text[i] == 'H' && text[i+1] == 'E') ||
            (text[i] == 'I' && text[i+1] == 'N') ||
            (text[i] == 'E' && text[i+1] == 'R')) {
            score += 5;
        }
    }
    
    return score;
}

// tursene na naj-dobroto otmestvane
int find_best_shift(int freq[ALPHABET]) {

    int best_shift = 0;
    int best_score = -1;

    for (int s = 0; s < ALPHABET; s++) {

        int sc = score_shift(freq, s);

        if (sc > best_score) {
            best_score = sc;
            best_shift = s;
        }
    }

    return best_shift;
}

// vuzstanovqvane na kliocha
void recover_key(const char *text, int key_len, char *key) {

    int len = strlen(text);

    printf("\n--- KEY RECOVERY ---\n");

    for (int i = 0; i < key_len; i++) {

        int freq[ALPHABET] = {0};

        for (int j = i; j < len; j += key_len) {
            freq[text[j] - 'A']++;
        }

        int shift = find_best_shift(freq);
        key[i] = 'A' + shift;

        printf("Position %d -> shift %d -> %c\n",
               i, shift, key[i]);
    }

    key[key_len] = '\0';
}

// dekriptira
void decrypt_vigenere(const char *text, const char *key, char *output) {

    int key_len = strlen(key);

    for (int i = 0; text[i]; i++) {

        int c = text[i] - 'A';
        int k = key[i % key_len] - 'A';

        output[i] = ((c - k + 26) % 26) + 'A';
    }

    output[strlen(text)] = '\0';
}

// podobrqvane na kliocha
void refine_key(const char *text, char *key) {

    char best_plain[MAX_TEXT];
    char temp_plain[MAX_TEXT];
    char temp_key[100];

    decrypt_vigenere(text, key, best_plain);
    int best_score = score_text(best_plain);

    int key_len = strlen(key);

    for (int i = 0; i < key_len; i++) {

        char original = key[i];

        for (char c = 'A'; c <= 'Z'; c++) {

            temp_key[0] = '\0';
            strcpy(temp_key, key);

            temp_key[i] = c;

            decrypt_vigenere(text, temp_key, temp_plain);

            int score = score_text(temp_plain);

            if (score > best_score) {
                best_score = score;
                strcpy(key, temp_key);
                strcpy(best_plain, temp_plain);
            }
        }

        key[i] = key[i]; // zapazva naj-dobriq
    }
}

// naj-dobriq klioch ot razlichni key lengths
void find_best_key(const char *text, char *best_key, char *best_plain) {

    int best_score = -999999;

    char key[100];
    char decrypted[MAX_TEXT];

    for (int key_len = 1; key_len <= 9; key_len++) {

        recover_key(text, key_len, key);
        refine_key(text, key);
        decrypt_vigenere(text, key, decrypted);

        int score = score_text(decrypted);
		score -= key_len * 2;
		
        if (score > best_score) {
            best_score = score;
            strcpy(best_key, key);
            strcpy(best_plain, decrypted);
        }
    }
}

int main() {

    char cipher[] =
    "Uhrzg hbe uwb ecfc og cbvuabudtvvi h cogtjitl netitv Quo wby va vv wale vb uv cinpym vokt uhrzg hbe pbiqqbclz nb lgmscjeakklc aod gpg vdhfr jia pc tp mnsg pd sp cbursscbtrl vokt uhrzg hbe oo bjxpyut drnkjseocvmu Are gieav totioq qu mkr noem fppfjchtv";

    char text[MAX_TEXT];
    normalize_text(cipher, text);

    printf("TEXT:\n%s\n", text);

    print_histogram(text);

    char best_key[100];
    char best_plain[MAX_TEXT];

    find_best_key(text, best_key, best_plain);

    printf("\n=== BEST RESULT ===\n");
    printf("Key: %s\n", best_key);
    printf("Plaintext:\n%s\n", best_plain);

    return EXIT_SUCCESS;
}