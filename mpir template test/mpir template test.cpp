#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpir.h"
#include "mpirxx.h"

int main(int argc, char** argv) {

	mpz_class a = 2;
	mpz_class b = 3;
	mpz_class c = a * a + b * b;
	gmp_printf("c=%Zd\n", c);

	return 0;

}