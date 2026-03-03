#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 256

// dekriptira edin simvol
char caesar_decrypt_char(char c, int k) {
    if (isupper(c)) {
        return ((c - 'A' - k + 26) % 26) + 'A';
    }
    return c;
}

// cql tekst s daden klioch
void caesar_decrypt_text(const char *input, char *output, int k) {
    for (int i = 0; input[i] != '\0'; i++) {
        output[i] = caesar_decrypt_char(input[i], k);
    }
    output[strlen(input)] = '\0';
}

int main() {

    char ciphertext[] = "WKLV LV D VHFUHW PHVVDJH";
    char decrypted[MAX_LEN];

    printf("Ciphertext: %s\n\n", ciphertext);
    printf("Brute-force results:\n");
    printf("--------------------\n");

    for (int key = 1; key <= 25; key++) {
        caesar_decrypt_text(ciphertext, decrypted, key);
        printf("Key %2d: %s\n", key, decrypted);
    }

    return EXIT_SUCCESS;
}