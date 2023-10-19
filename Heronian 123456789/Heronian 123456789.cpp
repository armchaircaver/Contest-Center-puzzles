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
#include <chrono>
#include <thread>



class CandidateTwosquares {
public:
	std::map<std::string, std::vector <std::vector<int64_t>>> cand_twosquares;

	CandidateTwosquares() {
		std::cout << "loading cand_twosquares 123456789 ...\n";

		std::ifstream input("cand_twosquares 123456789.json");
		nlohmann::json j;

		input >> j;

		cand_twosquares = j;
		std::cout << cand_twosquares.size() << " cand_twosquares 123456789 loaded\n";
		std::cout.flush();
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
	if (c2 > b * b && C2s.find(c2) != C2s.end()) {
		int64_t c = (int64_t)sqrt((long double)c2);
		if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
			std::string Area_st = std::to_string(Area);
			if (Area_st.find('0') == std::string::npos ) {
				std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
				print_time();
				std::cout.flush();
			}
		}
	}
	c2 = a * a + b * b + 2 * d;
	//std::cout << "c2 (+2d) = " << c2 << ", c=" << sqrt(c2) << "\n";
	if (c2 > b * b && C2s.find(c2) != C2s.end()) {
		int64_t c = (int64_t)sqrt((long double)c2);
		if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
			std::string Area_st = std::to_string(Area);
			if (Area_st.find('0') == std::string::npos ) {
				std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
				print_time();
				std::cout.flush();

			}
		}
	}
}

int main(int argc, char* argv[]) {

	int counter = 0;

	int64_t start = 935000000;
	if (argc > 1)
		start = atoll(argv[1]);

	print_time();
	std::cout.flush();


	for (auto x : cts.cand_twosquares) {
		int64_t c = stoi(x.first);
		C2s.insert(c * c);
	}

	int64_t lastgroup = 0;

	

	//for (auto A : cts.cand_twosquares) {
	for( auto A = cts.cand_twosquares.rbegin(); A != cts.cand_twosquares.rend(); ++A){
		int64_t a = stoi(A->first);

		if (a > start)
			continue;

		if (a / 1000000 != lastgroup) {
			std::cout << "starting group " << a / 1000000 << "\n";
			std::cout.flush();
		}

		lastgroup = a / 1000000;

		if (a != 134297658) continue;
		//std::cout << "a=" << a << "\n";

		for (auto& B : cts.cand_twosquares) {


			int64_t b = stoi(B.first);
			if (b <= a)
				continue;
			if (b != 587364219)	continue;

			counter++;
			if (counter % 5000000 == 0) {
				//print_time();
				//std::cout << "a= "<<A->first<< ", b= " << B.first << "\n";
				//std::cout.flush();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				//std::cout << " after sleep: ";
				//print_time();
			}

			for (auto& pq : A->second) {
				int64_t p = pq[0];
				int64_t q = pq[1];

				for (auto& uv : B.second) {
					int64_t u = uv[0];
					int64_t v = uv[1];
					std::cout << "p, q, u, v = " << p << "," << q << "," << u << "," << v << "\n";
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
	std::cout.flush();
}

/*

*/