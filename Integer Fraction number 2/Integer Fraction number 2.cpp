/*
Find 3 distinct positive integers x, y, z such that the fractions
123x2+456y2+7890z2 / 123x+456y+7890z

456x2+7890y2+123z2 / 456x+7890y+123z

7890x2+123y2+456z2 / 7890x+123y+456z
are all integers.

*/
#include <cstdio>
#include <cstdint>
#include "../Pythag/gcd.h"


uint64_t bestZ = 5413980;

uint64_t lcm(uint64_t x, uint64_t y) {
    return (x * y) / gcd(x, y);
}

uint64_t expand123(uint64_t x, uint64_t y, uint64_t z) {

    uint64_t n = 456 * x * x + 7890 * y * y + 123 * z * z;
    uint64_t d = 456 * x + 7890 * y + 123 * z;
    uint64_t f1 = d / bgcd(n, d);

    if (z * f1 > bestZ)
        return 0;


    n = (123 * x * x + 456 * y * y + 7890 * z * z);
    d = 123 * x + 456 * y + 7890 * z;
    uint64_t f2 = d / bgcd(n, d);

    uint64_t L12 = lcm(f1, f2);
    if (z * L12 > bestZ)
        return 0;


    n = 7890 * x * x + 123 * y * y + 456 * z * z;
    d = 7890 * x + 123 * y + 456 * z;
    uint64_t f3 = d / bgcd(n, d);

    uint64_t f = lcm(f3, L12);
    if (f * z > bestZ)
        return 0;

    z *= f;

    bestZ = z;
    return f;

}

bool test(uint64_t x, uint64_t y, uint64_t z) {

    uint64_t n = 123 * x * x + 456 * y * y + 7890 * z * z;
    uint64_t d = 123 * x + 456 * y + 7890 * z;
        if (n % d)return false;

        n = 456 * x * x + 7890 * y * y + 123 * z * z;
        d = 456 * x + 7890 * y + 123 * z;
            if (n % d)return false;

            n = 7890 * x * x + 123 * y * y + 456 * z * z;
            d = 7890 * x + 123 * y + 456 * z;
            if (n % d)return false;

            return true;
}


void search() {
    uint64_t M = 1ULL << 63;
    uint64_t N = 5000;
    for (uint64_t x = 1; x < N; x++) {
        printf("x=%llu\n", x);
            for (uint64_t y = x + 1; y < N; y++) {
                uint64_t g1 = gcd(x, y);
                for (uint64_t z = y + 1; z < N; z++) {
                    if (gcd(x, g1) > 1)
                        continue;
                    uint64_t f = expand123(x, y, z);
                    if (f) {
                        uint64_t p = f * x, q = f * y, r = f * z;
                        if (p + q + r < M) {
                            M = p + q + r;
                                if (!test(p, q, r))
                                    printf("Error in %llu %llu %llu\n", p, q, r);
                            uint64_t g = gcd(p, gcd(q, r));
                            printf("starting point= %llu %llu %llu ", x, y, z);
                            printf(", best solution x=%llu, y=%llu, z=%llu,  g=%llu \n", p, q, r, g);
                        }
                    }
                }
            }
    }
}

int main() {
    search();
    return 0;
}
