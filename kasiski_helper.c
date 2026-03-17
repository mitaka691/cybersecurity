#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIST 100

// gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// na masiv
int gcd_array(int arr[], int n) {

    if (n == 0)
        return 0;

    int result = arr[0];

    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }

    return result;
}

void kasiski_helper(const char *text) {

    int len = strlen(text);
    int distances[MAX_DIST];
    int dist_count = 0;

    printf("\n--- KASISKI ANALYSIS ---\n");

    for (int i = 0; i < len - 2; i++) {

        char trigram[4];

        trigram[0] = text[i];
        trigram[1] = text[i + 1];
        trigram[2] = text[i + 2];
        trigram[3] = '\0';

        for (int j = i + 1; j < len - 2; j++) {

            if (strncmp(trigram, &text[j], 3) == 0) {

                int distance = j - i;

                printf("Found \"%s\": Pos %d & Pos %d -> Distance: %d\n",
                       trigram, i, j, distance);

                if (dist_count < MAX_DIST) {
                    distances[dist_count++] = distance;
                }
            }
        }
    }

    printf("\nDistances collected: ");
    for (int i = 0; i < dist_count; i++) {
        printf("%d ", distances[i]);
    }

    printf("\n");

    int key_length = gcd_array(distances, dist_count);

    if (key_length > 1)
        printf("\nPossible key length (GCD): %d\n", key_length);
    else
        printf("\nCould not determine key length reliably.\n");
}

int main() {

    char cipher[] =
    "LXFOPVEFRNHRLXFOPVEFRNHRLXFOPVEFRNHR";

    kasiski_helper(cipher);

    return EXIT_SUCCESS;
}