#include <ctype.h> // за isupper()
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXN 1000


char caesar_encrypt_char(char symbol, int key) {
if (isupper(symbol)) {
return ( (symbol - 'A' + key) % 26 ) + 'A';

}else if(islower(symbol)){
    return ( (symbol - 'a' + key) % 26 ) + 'a';
}

return symbol; // Ако не е буква (напр. цифра), връщаме без промяна
}


char caesar_decrypt_char(char symbol, int key) {
if (isupper(symbol)) {
    return ( (symbol - 'A' + key) % 26 ) + 'A';
}else if(islower(symbol)){
    return ( (symbol - 'a' + key) % 26 ) + 'a';
}
return symbol;
}

char* caesar_encrypt(char* plaintext, int key){
    int length=strlen(plaintext);
    char* cipher = malloc(sizeof(char) * (length+1));
    int index=0;
    while(plaintext[index] !='\0'){
        cipher[index] = caesar_encrypt_char(plaintext[index], key);
        index++;
    }
    cipher[index]='\0';
    return cipher;
}

char* caesar_decrypt(char* cipher, int key){
    int length=strlen(cipher);
    char* plaintext = malloc(sizeof(char) * (length+1));
    int index=0;
    while(cipher[index] !='\0'){
        plaintext[index] = caesar_encrypt_char(cipher[index], key);
        index++;
    }
    plaintext[index]='\0';
    return plaintext;
}

int main(int argc, char **argv){
    char plaintext[MAXN];
    strcpy(plaintext, argv[1]);

    int key = strtol(argv[2], NULL, 10);

    char* cipher = caesar_encrypt(plaintext, key);
    printf("Encrypted: %s\n", cipher);

    char* decipher = caesar_decrypt(cipher, key);
    printf("Decrypted: %s\n", decipher);

    return EXIT_SUCCESS;
}
