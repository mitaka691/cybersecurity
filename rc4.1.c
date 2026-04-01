#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rc4_crypt(unsigned char *key, int keylen, unsigned char *data, int datalen, unsigned char *output) {
    unsigned char S[256];
    unsigned char temp;
    int i = 0, j = 0;

    for (i = 0; i < 256; i++) S[i] = i;

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keylen]) % 256;
        int tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    i = 0; j = 0;
    for (int k = 0; k < datalen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        char keystreamByte = S[(S[i] + S[j]) % 256];
        output[k] = data[k] ^ keystreamByte;
    }
}

int main() {
    unsigned char key[] = "Key";
    unsigned char plaintext[] = "Wikipedia";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[10];

    printf("Plaintext: %s\n", plaintext);
    rc4_crypt(key, strlen((char*)key), plaintext, strlen((char*)plaintext), ciphertext);
    
    printf("Ciphertext (Hex): ");
    for(int i=0; i<plaintext_len; i++) printf("%02X ", ciphertext[i]);
    printf("\n");
    
    return EXIT_SUCCESS;
}