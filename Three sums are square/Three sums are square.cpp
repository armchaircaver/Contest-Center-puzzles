#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpir.h"
#include "mpirxx.h"
#include <string>     // std::string, std::to_string
#include "FactorsA.h"
#include <functional>

mpz_class fourth, a4,b4,c4;
uint64_t MAX = 1000;

void printarray(uint64_t* primearray, int pasize) {
    printf("[");
    std::sort(primearray, primearray + pasize);
    for (int it = 0; it != pasize; ++it) {
        if (it == pasize - 1)
            printf("%llu", primearray[it]);
        else
            printf("%llu, ", primearray[it]);
    }
    printf("]");
}

uint64_t euclid_gcd(uint64_t n1, uint64_t n2) {
    while (n2) {
        uint64_t tmp = n1;
        n1 = n2;
        n2 = tmp % n2;
    }
    return n1;
}

void search() {
    printf("searching pythagorean quadruples with a,b,c < MAX=%llu\n", MAX);
    int numfactors= 0;
    uint64_t* factorsarray = new uint64_t[193536];
    int psize = 0;
    uint64_t parray[64];
    int count = 0;

    // https://en.wikipedia.org/wiki/Pythagorean_quadruple#Primitive_Pythagorean_quadruples_with_small_norm
    for (uint64_t a = 10; a <= MAX; a += 10)
    {
        printf("testing a=%llu\n", a);
        for (uint64_t b = 5; b <= MAX; b += 5) {

            //for fourth power sum to be square, two of a, b, c must be 0 mod 5
             // and two of a, b, c must be even(by analysing residues mod 4)


            uint64_t g = euclid_gcd(a, b);
            if (b % 2) {
                allfactors(a * a + b * b, factorsarray, numfactors);

                std::sort(factorsarray, factorsarray + numfactors);

                for (int i = 0; i < numfactors; i++) {
                    uint64_t p = factorsarray[i];

                    if (p * p >= a * a + b * b)
                        break;
                    uint64_t c = (a * a + b * b - p * p) / (2 * p);
                    if (c >= MAX)
                        continue;
                    if (euclid_gcd(g, c) > 1)
                        continue;
                    count++;
                    //fourth = pow(a, 4) + pow(b, 4) + pow(c, 4);
                    mpz_ui_pow_ui(a4.get_mpz_t(), a, 4);
                    mpz_ui_pow_ui(b4.get_mpz_t(), b, 4);
                    mpz_ui_pow_ui(c4.get_mpz_t(), c, 4);
                    fourth = a4 + b4 + c4;

                    if (mpz_perfect_square_p(fourth.get_mpz_t()))
                        printf("solution, %llu, %llu, %llu\n", a, b, c);
                }
            }
            else { // a % 2 == 0 and b % 2 == 0
                uint64_t l = a / 2;
                uint64_t m = b / 2;
                allfactors(l * l + m * m, factorsarray, numfactors);
                std::sort(factorsarray, factorsarray + numfactors);

                for (int i = 0; i < numfactors; i++) {
                    uint64_t n = factorsarray[i];
                    if (n * n >= l * l + m * m)
                        break;
                    uint64_t c = (l * l + m * m - n * n) / n;
                    if (c >= MAX)
                        continue;
                    if (euclid_gcd(g, c) > 1)
                        continue;
                    count++;
                    //fourth = pow(a, 4) + pow(b, 4) + pow(c, 4);
                    mpz_ui_pow_ui(a4.get_mpz_t(), a, 4);
                    mpz_ui_pow_ui(b4.get_mpz_t(), b, 4);
                    mpz_ui_pow_ui(c4.get_mpz_t(), c, 4);
                    fourth = a4 + b4 + c4;

                    if (mpz_perfect_square_p(fourth.get_mpz_t()))
                        printf("solution, %llu, %llu, %llu\n", a, b, c);
                }
            }
        }
    }
    printf("search completed for MAX=%llu, %d fourth powers examined\n", MAX, count);
}



int main(int argc, char** argv)
{
     if (argc >= 2)
        MAX = atol(argv[1]);

    search();
}