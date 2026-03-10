#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void vigenere_encrypt(const char *plaintext, const char *key, char *output) {
    int key_len = strlen(key);
    int key_index = 0; // koq bukva izpolzvame

    for (int i = 0; plaintext[i] != '\0'; i++) {
        char p = toupper(plaintext[i]);

        if (isalpha(p)) {

            // otmestvame ot kliocha
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            // kriptirane
            output[i] = ((p - 'A' + shift) % 26) + 'A';

            // minavane na sledvashtata bukva
            key_index++;

        } else {
            // ne kriptirame specialni simvoli
            output[i] = plaintext[i];
        }
    }

    output[strlen(plaintext)] = '\0';
}

void vigenere_decrypt(const char *ciphertext, const char *key, char *output) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);

        if (isalpha(c)) {

            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            output[i] = ((c - 'A' - shift + 26) % 26) + 'A';

            key_index++;
        } 
        else {
            output[i] = ciphertext[i];
        }
    }

    output[strlen(ciphertext)] = '\0';
}

int main() {

    FILE *fin = fopen("encrypted.txt", "r");
    FILE *fkey = fopen("key.txt", "r");
    FILE *fout = fopen("decrypted.txt", "w");

    if (!fin || !fkey || !fout) {
        printf("Error opening files.\n");
        return 1;
    }

    char ciphertext[1024];
    char key[100];
    char decrypted[1024];

    fgets(ciphertext, sizeof(ciphertext), fin);
    fgets(key, sizeof(key), fkey);

    key[strcspn(key, "\n")] = '\0';

    vigenere_decrypt(ciphertext, key, decrypted);

    fprintf(fout, "%s", decrypted);

    fclose(fin);
    fclose(fkey);
    fclose(fout);

    printf("Decryption complete.\n");

    return EXIT_SUCCESS;
}

/*int main() {

    char plaintext[] = "ATTACK AT DAWN";
    char key[] = "LEMON";
    char encrypted[256];

    vigenere_encrypt(plaintext, key, encrypted);

    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %s\n", key);
    printf("Encrypted : %s\n", encrypted);

    return EXIT_SUCCESS;
}*/

