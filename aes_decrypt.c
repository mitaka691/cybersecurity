#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("An error occurred within OpenSSL logic.\n");
    exit(1);
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

char* read_binary_file(const char* filename, size_t* out_size) {
    // 1. Отваряме файла в бинарен режим за четене ("rb")
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // 2. Намираме големината на файла
    fseek(file, 0, SEEK_END); // Отиваме в края на файла
    long size = ftell(file);  // Взимаме текущата позиция (големината в байтове)
    rewind(file);             // Връщаме се в началото на файла (еквивалентно на fseek(file, 0, SEEK_SET))

    if (size < 0) {
        perror("Грешка при определяне размера на файла");
        fclose(file);
        return NULL;
    }

    // 3. Заделяме памет за съдържанието
    // Добавяме +1 байт за терминираща нула ('\0') за всеки случай, 
    // ако решиш да го ползваш като нормален стринг по-късно.
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // 4. Прочитаме данните в буфера
    size_t bytes_read = fread(buffer, 1, size, file);
    if (bytes_read != (size_t)size) {
        perror("Error reading file");
        free(buffer); // Освобождаваме паметта при грешка
        fclose(file);
        return NULL;
    }

    // Слагаме терминираща нула (не пречи на бинарните данни)
    buffer[size] = '\0';

    // 5. Записваме размера, ако потребителят е подал валиден указател
    if (out_size) {
        *out_size = size;
    }

    // 6. Затваряме файла и връщаме буфера
    fclose(file);
    return buffer;
}

int main() {
    unsigned char *key = (unsigned char *)"0123456789012345";
    
    size_t* cipher_size;
    unsigned char *ciphertext = read_binary_file("cipher.bin", cipher_size);
    
    printf("Cipher Text: %s\n", ciphertext);

    char plaintext[1000];
    int plaintext_len = decrypt(ciphertext, strlen((char *)ciphertext), key, plaintext);

    printf("Plaintext is (%d bytes): %s", plaintext_len, plaintext);

    return EXIT_SUCCESS;
}