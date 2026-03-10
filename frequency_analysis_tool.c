#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void print_histogram(const char *text) {
    int counts[26] = {0};
    int total_letters = 0;

    // Prebroqvane
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = toupper(text[i]) - 'A';
            counts[index]++;
            total_letters++;
        }
    }

    // Vizualizaciq
    printf("\n--- FREQUENCY HISTOGRAM ---\n");

    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            printf("%c (%3d): ", 'A' + i, counts[i]);

            // zvezdichki <3
            for (int j = 0; j < counts[i]; j++) {
                printf("*");
            }

            printf("\n");
        }
    }
}

int main() {

    char text[] = "ALA BALA NICA TURSKA PANICA";

    print_histogram(text);

    return EXIT_SUCCESS;
}