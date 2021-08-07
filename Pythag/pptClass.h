#pragma once
#include <cstdint>
#include "gcd.h"

struct pythagTriple { uint64_t a; uint64_t b; uint64_t c; };

class Ppt {
	uint64_t m;
	uint64_t LIM = 1000;
	uint64_t n;

	void progress_mn() {
		n += 2;
		if (n >= m) {
			m++;
			if (m % 2) n = 2; else n = 1;
		}
	}

public:
	Ppt(uint64_t lim) {
		LIM = lim;
		m = 2;
		n = 1;
	}


	pythagTriple next() {
		while (true) {
			if (m * m >= LIM)
				return pythagTriple{ 0,0,0 };
			while (bgcd(m, n) > 1)
				progress_mn();
			pythagTriple r = { (m * m - n * n), 2 * m * n, (m * m + n * n) };
			progress_mn();
			if (r.c <= LIM) {
				return r;
			}
		}
	}

	pythagTriple first() {
		return next();
	}
};