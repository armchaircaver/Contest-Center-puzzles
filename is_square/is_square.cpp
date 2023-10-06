#include <cstdint>
#include <cmath>
#include <intrin.h> // _bittest64

// is_square function based on fenderbender's code
// https://mersenneforum.org/showpost.php?p=110896

bool is_square_fb(uint64_t n) 
{

	uint64_t m;

	// start with mod 128 rejection. 82% rejection rate
	// VERY fast, can read bits directly
	m = n & 127; // n mod 128
	if ((m * 0x8bc40d7d) & (m * 0xa1e2f5d1) & 0x14020a) return false;


	//Other modulii share one BigInt modulus.
	uint64_t largeMod = n % (63UL * 25 * 11 * 17 * 19 * 23 * 31); // SLOW, bigint modulus

	// residues mod 63. 75% rejection
	m = largeMod % 63; // fast, all 32-bit math
	if ((m * 0x3d491df7) & (m * 0xc824a9f9) & 0x10f14008) return false;

	// residues mod 25. 56% rejection
	m = largeMod % 25;
	if ((m * 0x1929fc1b) & (m * 0x4c9ea3b2) & 0x51001005) return false;

	// residues mod 31. 48.4% rejection
	//  Bloom filter has a little different form to keep it perfect
	m = 0xd10d829a * (largeMod % 31);
	if (m & (m + 0x672a5354) & 0x21025115) return false;


	// residues mod 23. 47.8% rejection
	m = largeMod % 23;
	if ((m * 0x7bd28629) & (m * 0xe7180889) & 0xf8300) return false;

	// residues mod 19. 47.3% rejection
	m = largeMod % 19;
	if ((m * 0x1b8bead3) & (m * 0x4d75a124) & 0x4280082b) return false;

	// residues mod 17. 47.1% rejection
	m = largeMod % 17;
	if ((m * 0x6736f323) & (m * 0x9b1d499) & 0xc0000300) return false;

	// residues mod 11. 45.5% rejection
	m = largeMod % 11;
	if ((m * 0xabf1a3a7) & (m * 0x2612bf93) & 0x45854000) return false;


	// Net nonsquare rejection rate: 99.92%

	// We COULD extend to another round, doing another BigInt modulus and
	// then followup rejections here, using
	// primes of  13 29 37 41 43 53.  That'd give 98% further rejection.
	// Empirical timing shows this second round would be useful for n>10^100 or so.

	   // VERY expensive final definitive test
	//uint64_t root = (uint64_t) sqrt((double)n); 
	uint64_t root = (uint64_t)sqrtl((long double)n);

	return root * root == n; // true if and only if n is a square
}

//-----------------------------------------------------------------------
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

//const int64_t MAXROOT = 1000000;
//const int64_t MAX = MAXROOT * MAXROOT;


/*
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
*/
bool is_square(uint64_t n) {
	//if (!mod64[n % 64]) return 0;
	//if (!(m64 & (1ULL << (n % 64)))) return 0;
	
	if (!_bittest64(&m64, n % 64)) return 0;
	if (!mod63[n % 63]) return 0;
	if (!mod65[n % 65]) return 0;
	
	uint64_t rt = (uint64_t)sqrtl((long double)n);

	// isqrt is an order of magnitude slower than sqrtl
	//int64_t rt = isqrt(n);

	return n == rt * rt;
}

//-----------------------------------------------------------------------

