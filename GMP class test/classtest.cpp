#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#pragma warning(disable: 4800)
#include <mpirxx.h>
//#pragma warning(default: 4800)

int main(void){
	mpz_class a, b, c;

	a = 1234;
	b = "-5678";
	c = a + b;
	std::cout << "sum is " << c << "\n";
	std::cout << "absolute value is " << abs(c) << "\n";

	return 0;
}