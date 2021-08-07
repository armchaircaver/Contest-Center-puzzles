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

char s0[10000];
char s1[10000];

int main(int argc, char** argv)
{

    uint64_t m = 5000000;
    if (argc >= 2)
        m = atoll(argv[1]);

    mpz_t x0;
    mpz_t x1;

    mpz_init(x0);
    mpz_init(x1);
  
    int len = 0;
    for (uint64_t n = m+2; ; n++)
    {
         if (n % 2) {
            mpz_ui_pow_ui(x1, n, 8);                    // x1=n^8
            len = gmp_snprintf(s1, 2000, "%Zd", x1);    // s1 = decimal string of x1
        }
        else {
            mpz_ui_pow_ui(x0, n, 8);                   // x0=n^8
            len = gmp_snprintf(s0, 2000, "%Zd", x0);   // s0 = decimal string of x0
        }
     
         if (is_anagram(s0, s1, len)) {
            std::cout << "match for n = " << n-1 <<" and "<< n << std::endl;
            gmp_printf("n**8 = % Zd\n", x0);
            gmp_printf("(n+/-1)**8 = % Zd\n", x1);
        }

        if (n % 1000000 == 0) {
            std::cout << "tested n = " << n << std::endl;
        }
        lastlen = len;
    }

    exit(0);
}
