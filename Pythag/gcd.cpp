#include <cstdint>
#include <intrin.h>

uint64_t gcd(uint64_t a, uint64_t b) {
	uint64_t c;
	while (a != 0LL) {
		c = a; a = b % a;  b = c;
	}
	return b;
}

// from https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/

static inline int __builtin_ctzll(unsigned long long x) {
    unsigned long ret;
    _BitScanForward64(&ret, x);
    return (int)ret;
}

uint64_t bgcd(uint64_t u, uint64_t v) {
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) {
            int64_t t = v;
            v = u;
            u = t;
        }
        v -= u;
    } while (v);
    return u << shift;
}