#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

void rc4(unsigned char *data, int data_len, unsigned char *key, int key_len) {
    unsigned char S[N];
    int i, j = 0, t;

    for (i = 0; i < N; i++)
        S[i] = i;

    for (i = 0; i < N; i++) {
        j = (j + S[i] + key[i % key_len]) % N;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = 0;
    j = 0;

    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        t = (S[i] + S[j]) % N;

        data[k] ^= S[t];
    }
}

int main() {
    char input_file[256];
    char output_file[256];
    char password[256];

    printf("Enter input file: ");
    scanf("%255s", input_file);

    printf("Enter output file: ");
    scanf("%255s", output_file);

    printf("Enter password: ");
    scanf("%255s", password);

    FILE *fin = fopen(input_file, "rb");
    if (!fin) {
        printf("Error opening input file!\n");
        return 1;
    }

    FILE *fout = fopen(output_file, "wb");
    if (!fout) {
        printf("Error opening output file!\n");
        fclose(fin);
        return 1;
    }

    fseek(fin, 0, SEEK_END);
    long file_size = ftell(fin);
    rewind(fin);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        printf("Memory allocation failed!\n");
        fclose(fin);
        fclose(fout);
        return 1;
    }

    if (fread(buffer, 1, file_size, fin) != file_size) {
        printf("Error reading file!\n");
        free(buffer);
        fclose(fin);
        fclose(fout);
        return 1;
    }

    rc4(buffer, file_size, (unsigned char *)password, strlen(password));

    fwrite(buffer, 1, file_size, fout);

    free(buffer);
    fclose(fin);
    fclose(fout);

    printf("Done!\n");

    
    system("pause");

    return EXIT_SUCCESS;
}
