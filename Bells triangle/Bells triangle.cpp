#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "mpirxx.h"
#include <fstream>

using std::vector;

vector<mpz_class> bell = { 2,3,5 };

mpz_class odd, even;

char sx[10000000];

void printbell() {
    for (auto x: bell)
        gmp_printf("%Zd,",x);
    printf("\n");
}

void dumpbell() {
    std::ofstream f;
    f.open("bell.txt");
    for (auto x : bell)
        f << x << "\n" ;
    f.close();
}

bool is_palindrome(char* sx, int lx){
    for (int i = 0; i <= lx / 2; i++)
        if (sx[i] != sx[lx - i-1])
            return false;
     return true;
}

int main(int argc, char** argv)
{
    printbell();
   for (int r = 3; ; r++){
       even = bell[0];
       bell[0] = bell[r - 1];
       int j = 1;
        // Fill for remaining values of j 
       for (j = 1; j < r; j++) {
           if (j % 2) {
               odd = bell[j];
               bell[j] = bell[j - 1] + even;
           }
           else {
               even = bell[j];
               bell[j] = bell[j - 1] + odd;
           }
        }
       if ( (r-1) % 2)
           bell.push_back(bell[r-1] + odd);
       else
           bell.push_back(bell[r-1] + even);

       if (mpz_perfect_square_p(bell[r-1].get_mpz_t()))
           gmp_printf("row %d, sum is square\n", r-1);

       int lx = gmp_snprintf(sx, 1000000, "%Zd", bell[r - 1]);
       if (is_palindrome(sx, lx))
           printf("row %d, sum is palindrome\n", r - 1);

        if (r < 8)
            printbell();

        if (r % 100 == 0) {
            printf("tested r=%d, length=%d\n", r, lx);
            dumpbell();
        }
    }
}