#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(long long n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    // samo do sqrt(n) i samo nechetni chisla
    for (long long i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    long long test_num = 27;

    if (is_prime(test_num)) {
        printf("%lld e PROSTO chislo.\n", test_num);
    } else {
        printf("%lld NE E prosto chislo.\n", test_num);
    }

    return EXIT_SUCCESS;
}