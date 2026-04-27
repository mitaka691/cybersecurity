#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorize_rsa(long long n) {
    printf("--- Zapochva faktorizirane na N = %lld ---\n", n);

    long long limit = (long long)sqrt(n);

    // proverqvame za 2
    if (n % 2 == 0) {
        long long p = 2;
        long long q = n / 2;

        printf("[USPEH] Otkriti mnozhiteli!\n");
        printf("p = %lld\n", p);
        printf("q = %lld\n", q);

        long long phi = (p - 1) * (q - 1);
        printf("Phi(n) = %lld\n", phi);
        return;
    }

    // samo nechetni chisla
    for (long long i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            long long p = i;
            long long q = n / i;

            printf("[USPEH] Otkriti mnozhiteli!\n");
            printf("p = %lld\n", p);
            printf("q = %lld\n", q);

            long long phi = (p - 1) * (q - 1);
            printf("Phi(n) = %lld\n", phi);

            return;
        }
    }

    printf("Ne byaha otkriti mnozhiteli.\n");
}

int main() {
    long long public_n = 3233;
    factorize_rsa(public_n);
    return EXIT_SUCCESS;
}