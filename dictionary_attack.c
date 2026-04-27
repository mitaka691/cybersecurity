#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <stdlib.h>

void dictionary_attack(const char *target_hash, const char *dict_file) {
    FILE *file = fopen(dict_file, "r");
    if (!file) {
        printf("Greshka pri otvarqneto na rechnika!\n");
        return;
    }

    char word[256];

    printf("--- Zapochva Dictionary Attack ---\n");

    while (fgets(word, sizeof(word), file)) {

    
        word[strcspn(word, "\n")] = 0;

        // heshirane
        char *computed_hash = crypt(word, target_hash);

        
        if (strcmp(computed_hash, target_hash) == 0) {
            printf("[USPEH] Parolata e namerena: %s\n", word);
            fclose(file);
            return;
        }
    }

    printf("[NEUSPEH] Parolata ne e v rechnika.\n");
    fclose(file);
}

int main() {
    // primeren hash ("password")
    const char *target_hash =
    "$6$salt$IxDD3jeSOb5eB1CX5LBsqZFVkJdido3OUILO5Ifz5iwMuTS4XMS130MTSuDDl3aCI6WouIL9AjRbLCelDCy.g."; 

    const char *dictionary = "rockyou_mini.txt";

    dictionary_attack(target_hash, dictionary);

    return EXIT_SUCCESS;
}