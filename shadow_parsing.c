#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char shadow_line[] = "bob:$6$xyz123$T5x/L.C8vB/O:19000:0:99999:7:::";

    char *username = NULL;
    char *hash = NULL;

    
    username = strtok(shadow_line, ":");

    
    hash = strtok(NULL, ":");

    if (username && hash) {
        printf("Target User: %s\n", username);
        printf("Target Hash: %s\n", hash);
    } else {
        printf("Greshka pri parsvane\n");
    }

    return EXIT_SUCCESS;
}