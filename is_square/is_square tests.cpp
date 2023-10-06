#include "is_square.h" 
#include <iostream>
#include "../Pythag/Timer.h"

void test_square_pm1(uint64_t n) {
	if (is_square(n - 1)) {
		std::cout << "is_square FAIL for " << n - 1 << "\n";
		exit(1);
	}
	if (!is_square(n)) {
		std::cout << "is_square FAIL for " << n << "\n";
		exit(1);
	}
	if (is_square(n + 1)) {
		std::cout << "FAIL for " << n + 1 << "\n";
		exit(1);
	}
	//std::cout << "near square tests successful for n= " << n << "\n";
}

int main() {

	if (!(is_square(0) && is_square(1))) {
		std::cout << "is_square FAIL for 0 and 1\n";
		exit(1);
	}

	for (uint64_t r = 2ull; r < 10000000; r++) {
		test_square_pm1(r * r);
	}

	for (int e = 2; e < 64; e += 2) {
		test_square_pm1(1ULL << e);
	}

	uint64_t r = (1ULL << 32) - 1000000;
	for (; r < (1ULL << 32); r++) {
		test_square_pm1(r * r);
	}
	std::cout << "All tests completed\n";

	Timer t;

	/*
	t.start();

	for (int64_t n = 2; n <= (1ULL << 32); n++) {
		int64_t n2 = n * n;
		if (n2 < 0)
			break;
		if (n % 100000000 == 0) {
			t.end();
			printf("tested n=%llu, %llu ms\n", n, t.ms());
			t.start();
		}
		if (is_square_fb(n2) && !is_square_fb(n2 + 1) && !is_square_fb(n2 - 1) ) continue;
		printf("is_square_fb failure for n=%llu, n^2=%llu\n", n, n2);
		std::cout << is_square_fb(n2) << "," << is_square_fb(n2 + 1) << "," << is_square_fb(n2 - 1) << "\n";
		exit(1);
	}
	*/
	//--------------------------------------------------------------------------------
	t.start();

	for (int64_t n = 2; n <= (1ULL << 32); n++) {
		int64_t n2 = n * n;
		if (n2 < 0)
			break;
		if (n % 100000000 == 0) {
			t.end();
			printf("is_square tested n=%llu, %llu ms\n", n, t.ms());
			t.start();
		}
		if (is_square(n2) && !is_square(n2 + 1) && !is_square(n2 - 1)) continue;
		printf("is_square failure for n=%llu, n^2=%llu\n", n, n2);
		std::cout << is_square(n2) << "," << is_square(n2 + 1) << "," << is_square(n2 - 1) << "\n";
		exit(1);
	}

}


