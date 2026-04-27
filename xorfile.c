#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("encrypted.bin", "wb");

    if (!in || !out) {
        printf("Greshka pri otvarqneto na faila!\n");
        return 1;
    }

    int ch;
    char key = 'X'; // XOR ????

    while ((ch = fgetc(in)) != EOF) {
        char encrypted = ch ^ key;
        fputc(encrypted, out);
    }

    fclose(in);
    fclose(out);

    printf("File successfully encrypted.\n");

    return EXIT_SUCCESS;
}