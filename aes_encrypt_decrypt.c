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


int decrypt(unsigned char *ciphertext, int ciphertext_len,
            unsigned char *key, unsigned char *plaintext) {

    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        handleErrors();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();

    plaintext_len = len;

    
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        printf("Decryption failed (bad padding or wrong key!)\n");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main() {
    unsigned char key[16] = "0123456789012345";

    unsigned char plaintext[] = "CyberSecurity Lab";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    printf("Original text: %s\n", plaintext);

    
    int cipher_len = encrypt(plaintext, strlen((char *)plaintext), key, ciphertext);

    printf("\nCiphertext (%d bytes):\n", cipher_len);
    for (int i = 0; i < cipher_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

   
    int decrypted_len = decrypt(ciphertext, cipher_len, key, decryptedtext);

    if (decrypted_len < 0) {
        printf("Decryption error!\n");
        return 1;
    }

    decryptedtext[decrypted_len] = '\0'; // null terminate

    printf("\nDecrypted text: %s\n", decryptedtext);

    return 0;
}