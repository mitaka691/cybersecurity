#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("OpenSSL error!\n");
    exit(1);
}

int encrypt(unsigned char *plaintext, int plaintext_len,
            unsigned char *key, unsigned char *ciphertext) {

    EVP_CIPHER_CTX *ctx;
    int len, ciphertext_len;

    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();

    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();

    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len,
            unsigned char *key, unsigned char *plaintext) {

    EVP_CIPHER_CTX *ctx;
    int len, plaintext_len;

    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        handleErrors();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();

    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        printf("Decryption failed (wrong key or corrupted data)\n");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Usage: %s [enc|dec] input_file output_file key\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    char *key_str = argv[4];

    // ключ
    unsigned char key[16] = {0};
    strncpy((char *)key, key_str, 16);

    FILE *fin = fopen(input_file, "rb");
    if (!fin) {
        printf("Error opening input file\n");
        return 1;
    }

    FILE *fout = fopen(output_file, "wb");
    if (!fout) {
        printf("Error opening output file\n");
        fclose(fin);
        return 1;
    }

    // размер на файла
    fseek(fin, 0, SEEK_END);
    long file_size = ftell(fin);
    rewind(fin);

    unsigned char *input_buffer = malloc(file_size);
    unsigned char *output_buffer = malloc(file_size + 16); // padding

    if (!input_buffer || !output_buffer) {
        printf("Memory allocation failed\n");
        fclose(fin);
        fclose(fout);
        return 1;
    }

    fread(input_buffer, 1, file_size, fin);

    int output_len;

    if (strcmp(mode, "enc") == 0) {
        output_len = encrypt(input_buffer, file_size, key, output_buffer);
    }
    else if (strcmp(mode, "dec") == 0) {
        output_len = decrypt(input_buffer, file_size, key, output_buffer);
        if (output_len < 0) {
            free(input_buffer);
            free(output_buffer);
            fclose(fin);
            fclose(fout);
            return 1;
        }
    }
    else {
        printf("Invalid mode! Use 'enc' or 'dec'\n");
        return 1;
    }

    fwrite(output_buffer, 1, output_len, fout);

    free(input_buffer);
    free(output_buffer);
    fclose(fin);
    fclose(fout);

    printf("Done.\n");

    return 0;
}