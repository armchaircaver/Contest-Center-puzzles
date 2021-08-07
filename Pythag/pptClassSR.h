#pragma once
#include <cstdint>
#include <vector>

struct pythagTriple { uint64_t a; uint64_t b; uint64_t c; };

class Ppt {
	struct MN { uint64_t m; uint64_t n; };
	std::vector<MN> s;
	uint64_t LIM = 1000;
	int i = 0;

public:
	Ppt(uint64_t lim) {
		LIM = lim;
		s.push_back( { 2,1 } );
	}

	pythagTriple next() {
		if (i >= s.size())
			return { 0,0,0 };

		MN x = s[i++];
		uint64_t mm = x.m * x.m;
		uint64_t mn = x.m * x.n;
		uint64_t nn = x.n * x.n;

		pythagTriple r = { mm - nn, 2 * mn, mm + nn };
		if (5 * mm - 4 * mn + nn <= LIM)
			s.push_back({ 2 * x.m - x.n, x.m });
		if (5 * mm + 4 * mn + nn <= LIM)
			s.push_back({ 2 * x.m + x.n, x.m });
		if (5 * nn + 4 * mn + mm <= LIM )
			s.push_back({ 2 * x.n + x.m, x.n });
		return r;

	}
};