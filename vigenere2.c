#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 1024

// enkriptirane
void vigenere_encrypt(const char *plaintext, const char *key, char *output)
{
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char p = plaintext[i];

        if (isalpha(p))
        {
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            if (islower(p))
                output[i] = ((p - 'a' + shift) % 26) + 'a';
            else
                output[i] = ((p - 'A' + shift) % 26) + 'A';

            key_index++;
        }
        else
        {
            output[i] = p;
        }
    }

    output[strlen(plaintext)] = '\0';
}

// dekriptirane
void vigenere_decrypt(const char *cipher, const char *key, char *output)
{
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; cipher[i] != '\0'; i++)
    {
        char c = cipher[i];

        if (isalpha(c))
        {
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            if (islower(c))
                output[i] = ((c - 'a' - shift + 26) % 26) + 'a';
            else
                output[i] = ((c - 'A' - shift + 26) % 26) + 'A';

            key_index++;
        }
        else
        {
            output[i] = c;
        }
    }

    output[strlen(cipher)] = '\0';
}

// main
int main()
{
    FILE *fin = fopen("encrypted.txt", "r");
    FILE *fkey = fopen("key.txt", "r");
    FILE *fout = fopen("decrypted.txt", "w");

    if (!fin || !fkey || !fout)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char text[MAXN];
    char key[MAXN];
    char result[MAXN];

   
    fgets(text, sizeof(text), fin);

    fgets(key, sizeof(key), fkey);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    vigenere_decrypt(text, key, result);
    // vigenere_encrypt(text, key, result);

    fprintf(fout, "%s", result);

    fclose(fin);
    fclose(fkey);
    fclose(fout);

    printf("Operation complete.\n");

    return EXIT_SUCCESS;
}