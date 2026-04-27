#include <stdio.h>
#include <stdlib.h>

// iterativen evklid
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    printf("GCD na 48 i 18 e: %lld\n", gcd(48, 18));       // 6
    printf("GCD na 65537 i 3120 e: %lld\n", gcd(65537, 3120)); // 1

    return EXIT_SUCCESS;
}