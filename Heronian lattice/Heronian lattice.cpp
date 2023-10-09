#include <map>
#include "../is_square/is_square.h"
#include <cstdio>
#include "../Heronian 12345678/json.hpp" 
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <time.h>
#include <unordered_set>
#include "../Partition odd even/robin_hood.h"

#define u uv[0]
#define v uv[1]

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

void print_time() {
	time_t my_time = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &my_time);
	printf("%s \n", str);
}

robin_hood::unordered_set<int64_t> C2s;

void verify(int64_t a, int64_t b, int64_t x, int64_t y){
	int64_t c2 = x * x + y * y;

	if ((a + b) * (a + b) == c2)
		return;
	if ((a - b) * (a - b) == c2)
		return;


	if (C2s.find(c2) != C2s.end()) {

		int64_t c = (int64_t)sqrt((long double)c2);
		if (c <= b )
			return;

		long double fD = sqrt((long double)((a + b + c) * (a + b - c)) * (long double)((b + c - a) * (a + c - b))) / 4.0 ;

		if (fD == 0.0)
			return;
		if (abs(fD - round(fD)) < 0.0001) {
			int64_t D = (int64_t)fD;
			std::string Area_st = std::to_string(D);
			if (Area_st.find('0') == std::string::npos && Area_st.find('9') == std::string::npos) {
				printf(" %llu %llu %llu %llu\n", a, b, c, D);
				print_time();
			}
		}
	}
}

int main() {

	print_time();


	// populate the c-squared set C2s
	for (auto x : cts.cand_twosquares) {
		int64_t c = stoi(x.first);
		C2s.insert(c * c);
	}


	for (auto& A : cts.cand_twosquares) {
		int64_t a = stoi(A.first);
		//if (a != 15487236 && a!= 17342865 && a!= 17862345) continue;
		//std::cout << "a=" << a << "\n";

		for (auto& B : cts.cand_twosquares) {
			int64_t b = stoi(B.first);
			if (b <= a)
				continue;
			//if (b != 51638427)	continue;

			for (auto& pq : A.second) {
				int64_t p = pq[0];
				int64_t q = pq[1];

				for (auto& uv : B.second) {

					// replaced with #define statement
					//int64_t u = uv[0];
					//int64_t v = uv[1];

					if (p == 0) {
						verify(a, b, u, q + v);
						verify(a, b, u, q - v);
						if (u) {
							verify(a, b, v, q + u);
							verify(a, b, v, q - u);
						}
						else
							verify(a, b, v, q); 
					}
					else {
						if (u) {
							verify(a, b, p + u, q + v);
							verify(a, b, p - u, q + v);
							verify(a, b, p - u, q - v);
							verify(a, b, p + u, q - v);

							verify(a, b, p + v, q + u);
							verify(a, b, p - v, q + u);
							verify(a, b, p - v, q - u);
							verify(a, b, p + v, q - u);
						}
						else {
							verify(a, b, p , q + v);
							verify(a, b, p , q - v);

							verify(a, b, p + v, q + u);
							verify(a, b, p - v, q + u);
						}
					}
				}
			}
		}
	}
}