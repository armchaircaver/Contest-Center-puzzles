#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpir.h"
#include "mpirxx.h"
#include <string>     // std::string, std::to_string

bool is_anagram(char* sx, char* sy, int lx){
      int count[10] = { 0 };

      for (int j = 0; j < lx;j++) {
          count[sx[j] - 48] ++;
          count[sy[j] - 48] --;
      }
    for (int k = 0; k < 10; k++) //comparing the count of chars in both strings
        if (count[k])
            return 0;
    return 1;
}

mpz_t x, y;
char sx[10000];
char sy[10000];

bool testpower(uint64_t n, uint64_t r, int p) {
    mpz_ui_pow_ui(x, n, p);
    mpz_ui_pow_ui(y, r, p);

    int lx = gmp_snprintf(sx, 10000, "%Zd", x);
    int ly = gmp_snprintf(sy, 10000, "%Zd", y);
    if (lx != ly)
        return false;

    return is_anagram(sx, sy, lx);

}


void search(mpz_class n) {

    if (n % 10 == 0)
        return;

    std::string s = std::to_string(n);
    reverse(s.begin(), s.end());

    uint64_t r = stoi(s);
    if (n >= r)
        continue;

    mpz_ui_pow_ui(x, n, 2);
    mpz_ui_pow_ui(y, r, 2);

    int lx = gmp_snprintf(sx, 10000, "%Zd", x);
    int ly = gmp_snprintf(sy, 10000, "%Zd", y);
    if (lx != ly)
        continue;

    if (is_anagram(sx, sy, lx)) {

        bool success = true;
        for (int p = 3; p <= 24;p++) {
            if (!testpower(n, r, p)) {
                if (p > 6) {
                    printf("n=%lld, r=%lld", n, r);
                    printf(", failed at p=%d\n", p);
                }
                success = false;
                break;
            }
        }
        if (success) {
            printf("success for n=%lld\n", n);
            exit(0);
        }

    }

    if (n % 1000000 == 1)
        printf("tested n=%lld\n", n);


}

int main(int argc, char** argv)
{
    mpz_init(x);
    mpz_init(y);

    // construct candidates   a  b-zeros z
    for (uint64_t a=1; a<102; a++)
        for (uint64_t z=1;z<102; z++){
            if (z == a)
                continue;
            for ( uint64_t b = 10; b<30; b++)
                mpz_ui_pow_ui(x, n, 2);
        }
    search();
}