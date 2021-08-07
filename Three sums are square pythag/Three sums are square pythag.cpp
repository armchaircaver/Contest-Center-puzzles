#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../Pythag/pptClassBerggren.h"
#include "../Pythag/Timer.h"
#include "mpir.h"
#include "mpirxx.h"

int64_t MAX = 1000;
mpz_class test, a2, a4, b2,b4 ;


int main(int argc, char** argv) {

	uint64_t hlim = 1000;
	if (argc >= 2)
		hlim = atoll(argv[1]);

	Ppt p = Ppt(hlim);
	uint64_t count = 0;
	Timer tim;
	tim.start();
	for (pythagTriple t = p.first(); t.a > 0; t = p.next()) {
		/*
	https://sites.google.com/site/tpiezas/016
		(ab) ^ 4 + (ac) ^ 4 + (bc) ^ 4 = (a4 + a2b2 + b4) ^ 2, if a ^ 2 + b ^ 2 = c ^ 2
			can (ab) ^ 2 + (ac) ^ 2 + (bc) ^ 2  be a square ?

			(ab) ^ 2 + (ac) ^ 2 + (bc) ^ 2 = (ab) ^ 2 + c ^ 4 = a ^ 4 + 3a ^ 2b ^ 2 + b ^ 4
			= (a^2+b^2)^2 +a^2b^2
			*/

		mpz_ui_pow_ui(a2.get_mpz_t(), t.a, 2);
		mpz_ui_pow_ui(b2.get_mpz_t(), t.b, 2);
		
		//test = a2 * a2 + 3 * a2 * b2 + b2 * b2;
		test = a2 * a2 + (3 * a2 + b2) * b2;
		if (mpz_perfect_square_p(test.get_mpz_t())) {
			mpz_class ab = mpz_class(t.a) * mpz_class(t.b);
			mpz_class ac = mpz_class(t.a) * mpz_class(t.c);
			mpz_class bc = mpz_class(t.b) * mpz_class(t.c);
			gmp_printf("solution ab, ac, bc, %Zd, %Zd, %Zd\n", ab,ac,bc);
			return 0;
		}

		count++;
	}
	tim.end();
	printf("%llu pythagorean triples in %llu ms\n", count, tim.ms());
	printf("max depth = %d\n", p.maxDepth());

}