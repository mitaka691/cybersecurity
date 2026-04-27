#include <stdio.h>
#include <string.h>
#include <crypt.h> 
#include <stdlib.h>

void crack_pin(const char *target_hash) {
    char guess[5]; 

    printf("--- Zapochva PIN Brute-Force ---\n");

    for (int i = 0; i <= 9999; i++) {
        
        sprintf(guess, "%04d", i);

        // heshirane
        char *computed_hash = crypt(guess, target_hash);

        
        if (strcmp(computed_hash, target_hash) == 0) {
            printf("[Uspeh] Parolata e: %s\n", guess);
            return;
        }
    }

    printf("[NEUSPEH] Parolata ne e 4 cifren PIN.\n");
}

int main() {
    char shadow_line[] = "bob:$6$xq7%3$03TJMkvoZmSoSVmWpDUuBvXNInUeIT3fLj6EvodCh1qFYjK9azoiyfxT4/gomNcpX.5Xfg08ZPU6U.xIHu8Pn.:";

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

    crack_pin(hash);

    return EXIT_SUCCESS;
}