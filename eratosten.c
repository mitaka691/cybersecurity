#include <stdio.h>
#include <stdlib.h>

void sieve_of_eratosthenes(int max) {
    // masiv
    int *primes = malloc((max + 1) * sizeof(int));

    // priemame che vsichni sa prosti
    for (int i = 0; i <= max; i++) primes[i] = 1;

    primes[0] = 0;
    primes[1] = 0;

    // algorituma
    for (int p = 2; p * p <= max; p++) {
        if (primes[p]) {
            // mahame kratnite na p
            for (int i = p * p; i <= max; i += p) {
                primes[i] = 0;
            }
        }
    }


    printf("Prosti chisla do %d: ", max);
    for (int p = 2; p <= max; p++) {
        if (primes[p]) printf("%d ", p);
    }
    printf("\n");

    free(primes);
}

int main() {
    sieve_of_eratosthenes(100);
    return EXIT_SUCCESS;
}