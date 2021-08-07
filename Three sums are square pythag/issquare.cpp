#include <cstdint>
#include <corecrt_math.h>
#include <intrin.h>

static
int mod64[64] = { 1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,
				 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,
				 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 };

long long m64 = 0b0000001000000010000000100001001000000010000000110000001000010011;

static
int mod65[65] = { 1,1,0,0,1,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,0,
				 0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,
				 0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,0,0,1,0,0,1 };

static
int mod63[63] = { 1,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,
				 0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,
				 0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0 };

const int64_t MAXROOT = 1000000;
const int64_t MAX = MAXROOT * MAXROOT;


// from https://stackoverflow.com/questions/21657491/an-efficient-algorithm-to-calculate-the-integer-square-root-isqrt-of-arbitrari
uint64_t isqrt_impl(uint64_t const n, uint64_t const xk) {
	uint64_t const xk1 = (xk + n / xk) / 2;
	return (xk1 >= xk) ? xk : isqrt_impl(n, xk1);
}

uint64_t isqrt(uint64_t const n)
{
	if (n == 0) return 0;
	if (n == 18446744073709551615ULL) return 4294967295ULL;
	return isqrt_impl(n, n);
}
bool is_square(int64_t n) {
	//if (!mod64[n % 64]) return 0;
	//if (!(m64 & (1ULL << (n % 64)))) return 0;
	if (! _bittest64( &m64 , n % 64)) return 0;
	if (!mod63[n % 63]) return 0;
	if (!mod65[n % 65]) return 0;

	int64_t rt = (int64_t)sqrtl((long double)n);
	//int64_t rt = isqrt(n);
	return n == rt * rt;
}


