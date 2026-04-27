#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

#define MAX_LINE 512

// ---------- Dictionary Attack ----------
int dictionary_attack(const char *target_hash, const char *dict_file, char *found_pass) {
    FILE *file = fopen(dict_file, "r");
    if (!file) {
        printf("Greshka pri otvarqne na rechnika!\n");
        return EXIT_SUCCESS;
    }

    char word[256];

    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\r\n")] = 0;

        char *computed = crypt(word, target_hash);

        if (strcmp(computed, target_hash) == 0) {
            strcpy(found_pass, word);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

// Brute Force PIN
int brute_force_pin(const char *target_hash, char *found_pass) {
    char guess[5];

    for (int i = 0; i <= 9999; i++) {
        sprintf(guess, "%04d", i);

        char *computed = crypt(guess, target_hash);

        if (strcmp(computed, target_hash) == 0) {
            strcpy(found_pass, guess);
            return 1;
        }
    }

    return EXIT_SUCCESS;
}

// Obrabotvane na edin red
void process_user(char *line, const char *dict_file) {
    char *username = strtok(line, ":");
    char *hash = strtok(NULL, ":");

    if (!username || !hash) {
        printf("Greshka pri parsvane!\n");
        return;
    }

    char found_pass[256];

    // Dictionary Attack
    if (dictionary_attack(hash, dict_file, found_pass)) {
        printf("%s: %s (dictionary)\n", username, found_pass);
        return;
    }

    // Brute-force PIN
    if (brute_force_pin(hash, found_pass)) {
        printf("%s: %s (brute-force)\n", username, found_pass);
        return;
    }

    
    printf("%s: [NERAZBITA]\n", username);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s shadow.txt dictionary.txt\n", argv[0]);
        return 1;
    }

    FILE *shadow = fopen(argv[1], "r");
    if (!shadow) {
        printf("Greshka pri otvarqne na shadow faila!\n");
        return 1;
    }

    printf("\n--- Rezultati ---\n");

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), shadow)) {
        line[strcspn(line, "\r\n")] = 0;
        process_user(line, argv[2]);
    }

    fclose(shadow);
    return EXIT_SUCCESS;
}