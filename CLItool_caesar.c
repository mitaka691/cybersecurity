#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// logika 

char caesar_encrypt_char(char c, int k) {
    if (isupper(c))
        return ((c - 'A' + k) % 26) + 'A';
    else if (islower(c))
        return ((c - 'a' + k) % 26) + 'a';
    else
        return c;
}

char caesar_decrypt_char(char c, int k) {
    if (isupper(c))
        return ((c - 'A' - k + 26) % 26) + 'A';
    else if (islower(c))
        return ((c - 'a' - k + 26) % 26) + 'a';
    else
        return c;
}


int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Usage:\n");
        printf("./caesar_tool -e input.txt key.txt output.txt\n");
        printf("./caesar_tool -d input.txt key.txt output.txt\n");
        return 1;
    }

    char mode = argv[1][1];   // -e ili-d
    char *input_file = argv[2];
    char *key_file = argv[3];
    char *output_file = argv[4];

    FILE *fin = fopen(input_file, "r");
    FILE *fkey = fopen(key_file, "r");
    FILE *fout = fopen(output_file, "w");

    if (!fin || !fkey || !fout) {
        printf("Error opening files.\n");
        return 1;
    }

    // klioch
    int key;
    fscanf(fkey, "%d", &key);


    key = key % 26;
    if (key < 0)
        key += 26;

    // simvol po simvol
    int ch;
    while ((ch = fgetc(fin)) != EOF) {

        if (mode == 'e')
            ch = caesar_encrypt_char(ch, key);
        else if (mode == 'd')
            ch = caesar_decrypt_char(ch, key);
        else {
            printf("Invalid mode. Use -e or -d.\n");
            return 1;
        }

        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fkey);
    fclose(fout);

    printf("Operation completed successfully.\n");

    return EXIT_SUCCESS;
}