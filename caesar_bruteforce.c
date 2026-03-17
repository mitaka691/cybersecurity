#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LETTERS_COUNT 26
#define MAXN 1000

// na edin simvol
char caesar_decrypt_char(char c, int key)
{
    if (isupper(c))
        return ((c - 'A' - key + 26) % 26) + 'A';
    else if (islower(c))
        return ((c - 'a' - key + 26) % 26) + 'a';

    return c;
}

// cql tekst
void caesar_decrypt(char *input, char *output, int key)
{
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        output[i] = caesar_decrypt_char(input[i], key);
    }

    output[len] = '\0';
}

// brute force
void bruteforce_attack(char *cipher)
{
    char buffer[MAXN];

    printf("\n--- BRUTE FORCE REPORT ---\n");

    for (int key = 0; key < LETTERS_COUNT; key++)
    {
        caesar_decrypt(cipher, buffer, key);
        printf("[Key %02d]: %s\n", key, buffer);
    }
}

// main
int main()
{
    char cipher[MAXN];
    printf("Enter cipher text:\n");
    fgets(cipher, sizeof(cipher), stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    bruteforce_attack(cipher);

    return EXIT_SUCCESS;
}