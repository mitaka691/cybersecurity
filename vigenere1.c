#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1024

char* vigenere_encrypt(const char *plaintext, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;
    int plaintext_len = strlen(plaintext);
    char* output = malloc(sizeof(char) * (plaintext_len + 1));

    for (int i = 0; plaintext[i] != '\0'; i++) {
        char symbol = plaintext[i];

        if (isalpha(symbol)) {
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';
            if(islower(symbol))
            {
                output[i] = ((symbol - 'a' + shift) % 26) + 'a';
            }
            else if(isupper(symbol))
            {
                output[i] = ((symbol - 'A' + shift) % 26) + 'A';
            }

            key_index++;
        } else {
            output[i] = plaintext[i];
        }
    }
    output[strlen(plaintext)] = '\0';

    return output;
}

char* vigenere_decrypt(const char *cipher, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;
    int cipher_len = strlen(cipher);
    char* plaintext = malloc(sizeof(char) * (cipher_len + 1));

    for (int i = 0; cipher[i] != '\0'; i++) {
        char symbol = cipher[i];

        if (isalpha(symbol)) {
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';
            if(islower(symbol))
            {
                plaintext[i] = ((symbol - 'a' - shift + 26) % 26) + 'a';
            }
            else if(isupper(symbol))
            {
                plaintext[i] = ((symbol - 'A' - shift + 26) % 26) + 'A';
            }

            key_index++;
        } else {
            plaintext[i] = cipher[i];
        }
    }
    plaintext[strlen(cipher)] = '\0';

    return plaintext;
}


int main()
{
    char plaintext[MAXN];
    scanf("%s", plaintext);

    char key[MAXN];
    scanf("%s", key);

    char* cipher = vigenere_encrypt(plaintext, key);
    printf("Encrypted: %s\n", cipher);

    char* deciphered = vigenere_decrypt(cipher, key);
    printf("Decrypted: %s\n", deciphered);

    return EXIT_SUCCESS;
}