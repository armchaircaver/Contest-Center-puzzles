#include <map>
//#include "../is_square/is_square.h"
#include <cstdio>
#include "json.hpp" 
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <time.h>
#include <unordered_set>
#include "../Partition odd even/robin_hood.h"



class CandidateTwosquares {
public:
	std::map<std::string, std::vector <std::vector<int64_t>>> cand_twosquares;

	CandidateTwosquares() {
		std::cout << "loading cand_twosquares ...\n";

		std::ifstream input("cand_twosquares.json");
		nlohmann::json j;

		input >> j;

		cand_twosquares = j;
		std::cout << cand_twosquares.size() << " cand_twosquares loaded\n";
	}
};

CandidateTwosquares cts;

robin_hood::unordered_set<int64_t> C2s;


void print_time() {
	time_t my_time = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &my_time);
	printf("%s \n", str);
}

void examine(int64_t a, int64_t b, int64_t d, int64_t twoArea) {

	if (twoArea % 20 == 0)
		return;

	//  area is divisible by 6
	if (twoArea % 12)
		return;

	int64_t Area = twoArea / 2;


	int64_t c2 = a * a + b * b - 2 * d;
	if ( C2s.find(c2) != C2s.end()) {
		int64_t c = (int64_t)sqrt((long double)c2);
		if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
			std::string Area_st = std::to_string(Area);
			if (Area_st.find('0') == std::string::npos && Area_st.find('9') == std::string::npos) {
				std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
				print_time();
			}
		}
	}
	c2 = a * a + b * b + 2 * d;
	//std::cout << "c2 (+2d) = " << c2 << ", c=" << sqrt(c2) << "\n";
	if (C2s.find(c2) != C2s.end()) {
		int64_t c = (int64_t)sqrt((long double)c2);
		if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
			std::string Area_st = std::to_string(Area);
			if (Area_st.find('0') == std::string::npos && Area_st.find('9') == std::string::npos) {
				std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
				print_time();

			}
		}
	}
}

int main() {

	print_time();


	for (auto x : cts.cand_twosquares) {
		int64_t c = stoi(x.first);
		C2s.insert(c*c);
	}

	for (auto A : cts.cand_twosquares) {
		int64_t a = stoi(A.first);
		//if (a != 15487236) continue;
		//std::cout << "a=" << a << "\n";


		for (auto& B : cts.cand_twosquares) {
			int64_t b = stoi(B.first);
			if (b < a)
				continue;
			//if (b != 51638427)	continue;

			for (auto& pq : A.second) {
				int64_t p = pq[0];
				int64_t q = pq[1];

				for (auto& uv : B.second) {
					int64_t u = uv[0];
					int64_t v = uv[1];

					if ((p * v) % 2 == (q * u) % 2) {
						examine(a, b, p * u + q * v, abs(p * v - q * u));
						if (p > 0 && u > 0) examine(a, b, p * u - q * v, p * v + q * u);
					}
					if ((p * u) % 2 == (q * v) % 2) {
						examine(a, b, p * v + q * u, abs(p * u - q * v));
						if (p > 0 && u > 0) examine(a, b, p * v - q * u, p * u + q * v);
					}
				}
			}
		}
	}



	std::cout << "end time : ";
	print_time();
}

/* 
Performance tuning attempts:
Time to first solution
without any mods:							2.3 min
(time to completion 22.5 min)
with string check to eliminate '0'& '9' :	6.5 min
with sprintf check to eliminate '0'& '9' :	>20 min
with sorting and eliminating duplicates :	3.5 min
with find c^2 in std::unordered_set			5.0 min
with find c^2 in robin_hood::unordered_set	2.0 min
test area%6=0								2.3

*/
