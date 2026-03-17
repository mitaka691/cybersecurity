#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LETTERS_COUNT 26

// count letters
int* count_letters(char* text)
{
    int* counts = malloc(sizeof(int) * LETTERS_COUNT);
    memset(counts, 0, sizeof(int) * LETTERS_COUNT);

    for(int i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            int index = toupper(text[i]) - 'A';
            counts[index]++;
        }
    }

    return counts;
}

// HISTOGRAM
void print_histogram(char* text)
{
    int* counts = count_letters(text);

    printf("\n--- FREQUENCY HISTOGRAM ---\n");

    for(int i = 0; i < LETTERS_COUNT; i++)
    {
        if(counts[i] > 0)
        {
            printf("%c (%3d): ", 'A' + i, counts[i]);

            for(int j = 0; j < counts[i]; j++)
            {
                printf("*");
            }

            printf("\n");
        }
    }

    free(counts);
}

// most common letter
char get_most_common_letter(char* text)
{
    int* counts = count_letters(text);

    int maxIndex = 0;
    for(int i = 1; i < LETTERS_COUNT; i++)
    {
        if(counts[i] > counts[maxIndex])
        {
            maxIndex = i;
        }
    }

    char letter = maxIndex + 'A';

    free(counts);
    return letter;
}

// dekriptirane
char caesar_decrypt_char(char c, int key)
{
    if(isupper(c))
        return ((c - 'A' - key + 26) % 26) + 'A';
    else if(islower(c))
        return ((c - 'a' - key + 26) % 26) + 'a';

    return c;
}

char* caesar_decrypt(char* cipher, int key)
{
    int len = strlen(cipher);
    char* result = malloc(len + 1);

    for(int i = 0; i < len; i++)
    {
        result[i] = caesar_decrypt_char(cipher[i], key);
    }

    result[len] = '\0';
    return result;
}

// fixed key fuknciq
int get_key(char common_letter, char expected_letter)
{
    return (common_letter - expected_letter + 26) % 26;
}

// analiz
void caesar_analyze(char* cipher)
{
    char common = get_most_common_letter(cipher);

    printf("\nMost common letter: %c\n", common);
    printf("\n--- POSSIBLE DECRYPTIONS ---\n");

    char candidates[] = {'E', 'T', 'A', 'O'};

    for(int i = 0; i < 4; i++)
    {
        int key = get_key(common, candidates[i]);
        char* decrypted = caesar_decrypt(cipher, key);

        printf("[Assuming %c] Key = %d -> %s\n",
               candidates[i], key, decrypted);

        free(decrypted);
    }
}

// main
int main()
{
    char cipher[1000];

    printf("Enter cipher text:\n");
    fgets(cipher, sizeof(cipher), stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    print_histogram(cipher);
    caesar_analyze(cipher);

    return EXIT_SUCCESS;
}