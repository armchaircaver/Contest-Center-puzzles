#include <cstdio>
#include "mpir.h"
#include "mpirxx.h"

/*
First and Last 20
Find the smallest integer N > 10**10 such that the first 20 digits of N**2 are
the same as the last 20 digits of N**2.
For example, the first 3 digits of 277363**2 = 76930233769
are the same as the last 3 digits. [No brute-force computer searches, please.]
*/

uint64_t ipow(int x, int p){
    if (p == 0) return 1;
    if (p == 1) return x;

    uint64_t tmp = ipow(x, p / 2);
    if (p % 2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}

mpz_class ten20=0, ten20modd=0, ten20plusd=0, tendm1=0, M=0, N=0;

void search(int D) {
    mpz_ui_pow_ui(ten20.get_mpz_t(), 10, D);
    //gmp_printf("ten20 =  %Z\n", ten20);

    for (int d = 1; d < 20; d++) {
        //ten20modd = 10 * *(D % d)
        mpz_ui_pow_ui(ten20modd.get_mpz_t(), 10, D%d);
        //gmp_printf("ten20modd =  %Zd\n", ten20modd);

        //ten20plusd = pow(10, D + d)
        mpz_ui_pow_ui(ten20plusd.get_mpz_t(), 10, D + d);
        //gmp_printf("ten20plusd =  %Zd\n", ten20plusd);

        printf("testing d=%d \n", d);
        //tendm1 = 10 * *d - 1
        mpz_ui_pow_ui(tendm1.get_mpz_t(), 10, d);
        tendm1 -= 1;

        for (uint64_t q = ipow(10, d - 1); q < ipow(10,d); q++) {
            M = (ten20plusd * q) / tendm1;
            //print(p, q, x, M, int(M * *0.5), M - int(M * *0.5) * *2)
            if (M > 0 && mpz_perfect_square_p(M.get_mpz_t())) {
                //N = int(M * *0.5)
                mpz_sqrt(N.get_mpz_t(), M.get_mpz_t());
                //assert N * N == M

                gmp_printf("q=%llu, M=%Zd = %Zd ^2\n", q, M, N);
            }
        }
    }
}

int main() {
    search(20);
}