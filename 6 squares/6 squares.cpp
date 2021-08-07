#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdio>
//#include "../Partition odd even/robin_hood.h"
#include <sstream>
#include "../Three sums are square pythag/issquare.cpp"
#include <unordered_map>
#include <algorithm>
#include "mpir.h"
#include "mpirxx.h"


/*
The numbers 1 and 44 form squares when they are concatenated in either order,
namely 144=12^2 and 441=21^2. Are there 3 integers A, B and C such that all 6 of 
their possible concatenations form squares? 
If not, what is the largest number of squares that can be formed by concatenating 3 integers? 
*/

//robin_hood::unordered_map< uint64_t, std::vector<uint64_t> >  numbers;
std::unordered_map< uint64_t, std::vector<uint64_t> > numbers;

mpz_class sq1, sq2;

std::string tostr(uint64_t n) {
    return (std::ostringstream() << std::dec << n).str();
}

void examine(uint64_t x) {
    auto s = numbers[x].size();
    uint64_t z = numbers[x].at(numbers[x].size() - 1);
    for (int i = 0; i < s - 1; i++) {
        uint64_t y = numbers[x].at(i);
        if (y == z)
            continue;

        sq1 = tostr(y) + tostr(z);
         if (mpz_perfect_square_p(sq1.get_mpz_t())) {
            printf("x,y,z = %llu, %llu, %llu\n", x, y, z);
        }

        sq2 = tostr(z) + tostr(y);
        if (mpz_perfect_square_p(sq2.get_mpz_t())) {
            printf("x,y,z2 = %llu, %llu, %llu\n", x, y, z);
        }
    }
}

mpz_class test;

void split(uint64_t s) {

    uint64_t p = 1; 
    uint64_t n = s;
    while (n) { n /= 10; p*=10; }

    uint64_t p10 = 10, x, y, z;
    while (1) {
        x = s / p10;
        y = s % p10;
        if (x == 0)
            break;
        if (y > 0) {
            z = y * (p / p10) + x;
            test = z;
            //if (z2 != z) {
            //    printf("%llu, %llu, %llu, %llu, %llu, %llu\n", z, z2, x,y, p, p10);
            //}

            if (is_square(z)) {
                // check 
                if (mpz_perfect_square_p(test.get_mpz_t()) == 0) {
                    gmp_printf("mismatch perfect square test %llu v. %Z\n", z, test);
                    exit(1);
                }

                //printf("found square: %llu, %llu, %llu, p=%llu, p10=%llu\n",x,y,z,p,p10);
                numbers[x].push_back(y);
                if (numbers[x].size() > 1)
                    examine(x);
                numbers[y].push_back(x);
                if (numbers[y].size() > 1)
                    examine(y);
            }
            else {
                // check 
                if (mpz_perfect_square_p(test.get_mpz_t() )){
                    gmp_printf("mismatch perfect square test %llu v. %Z\n",z,test);
                    exit(1);

                }
            }
        }
        p10 *= 10;
    }
}

int main() {

    for (uint64_t n = 1; n < 1000000000; n++) {
        split(n * n);
        if (n % 10000000 == 0) {
            std::cout << "n="<<n<<", "<< numbers.size() << " dictionary entries\n";
        }
    }
}