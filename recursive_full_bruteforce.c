#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
const int charset_len = 36;

int is_found = 0;


void generate_recursive(char *current_guess, int position, int max_length, const char *target_hash) {

    if (is_found) return;

    
    if (position > 0) {
        current_guess[position] = '\0';

        char *computed = crypt(current_guess, target_hash);

        if (strcmp(computed, target_hash) == 0) {
            printf("[USPEH] Parolata e: %s\n", current_guess);
            is_found = 1;
            return;
        }
    }

    
    if (position == max_length) return;

   
    for (int i = 0; i < charset_len; i++) {

        current_guess[position] = charset[i];

        generate_recursive(current_guess, position + 1, max_length, target_hash);

        if (is_found) return; 
    }
}

int main() {

    
    const char *target_hash = "$6$salt$i1etou/cjGIhaFRAAe9Ovyu8VW7eoR4C1h8EpVn8PpPcvBVwfsaYgJRGnPhBZyT5Z3JenrlmY/p02tjS7Gl0w/";

    char buffer[9]; // do 8 simvola + '\0'

    printf("--- Zapochva Recursive Brute-Force ---\n");

    generate_recursive(buffer, 0, 3, target_hash); // do tri simvola

    if (!is_found) {
        printf("[NEUSPEH] Parolata ne e namerena.\n");
    }

    return EXIT_SUCCESS;
}