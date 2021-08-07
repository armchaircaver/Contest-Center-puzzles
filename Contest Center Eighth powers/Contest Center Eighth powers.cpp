// https://stackoverflow.com/questions/15691477/c-mpir-mpz-t-to-stdstring

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpir.h"

bool is_anagram(char* sx, char* sy, int lx)
{
    int i = 0;
    while (sx[i] == sy[i])
        i++;

    int count[10] = { 0 };
    for (int j = i; j < lx;j++)
        count[sx[j] - 48] ++;

    for (int j = i; j < lx;j++) {
        count[sy[j] - 48] --;
        if (count[sy[j] - 48] < 0)
            return 0;
    }
    for (int k = 0; k < 10; k++) //comparing the count of chars in both strings
        if (count[k])
            return 0;
    return 1;
}


int main(int argc, char** argv)
{
    mpz_t x, y;

    mpz_init(x);
    mpz_init(y);
 
    //uint64_t n = 5623410; // 5474857;
    char sx[10000];
    char sy[10000];

    uint64_t m = 5000000;
    if (argc >= 2)
        m = atoll(argv[1]);

    // adjust so that m = 4 mod 9
    m -= m % 9;
    m += 4;


    for (uint64_t n = m; ; n+=9)
    {
        //std::cout << "n = " << n << std::endl;
        mpz_ui_pow_ui(x, n, 8);
        mpz_ui_pow_ui(y, n + 1, 8);
        int lx = gmp_snprintf(sx, 10000, "%Zd", x);
        int ly = gmp_snprintf(sy, 10000, "%Zd", y);
        if (lx != ly)
            continue;

        if (is_anagram(sx, sy, lx)) {
            std::cout << "match for n = " << n << std::endl;
            //gmp_printf("n**8 = % Zd\n", x);
            //gmp_printf("(n+1)**8 = % Zd\n", y);
        }

        //if (n % 10000000 < 9) {
        //    std::cout << "tested n = " << n << std::endl;
        //}
    }

    exit(0);
}
