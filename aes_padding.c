#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("OpenSSL error!\n");
    exit(1);
}

int encrypt(unsigned char *plaintext, int plaintext_len,
            unsigned char *key, unsigned char *ciphertext) {

    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

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

int main() {
    unsigned char key[16] = "0123456789012345";

    unsigned char plaintext[] = "ABCDE";

    unsigned char ciphertext[128];

    printf("Plaintext: %s\n", plaintext);
    printf("Plaintext length: %lu bytes\n", strlen((char *)plaintext));

    int cipher_len = encrypt(plaintext, strlen((char *)plaintext), key, ciphertext);

    printf("\nCiphertext (%d bytes):\n", cipher_len);

    for (int i = 0; i < cipher_len; i++) {
        printf("%02x ", ciphertext[i]);
    }

    printf("\n");

    printf("\nLast 11 bytes (padding block):\n");
    for (int i = cipher_len - 11; i < cipher_len; i++) {
        printf("%02x ", ciphertext[i]);
    }

    printf("\n");

    return 0;
}