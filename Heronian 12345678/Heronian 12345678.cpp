#include <map>
#include "../is_square/is_square.h"
#include <cstdio>
#include "json.hpp" 
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>

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

//std::vector <std::vector<int64_t>>T;
int64_t T[100000];
int ti = 0;

//typedef struct ipair { int64_t x[2]; } ipair;
//int64_t Ts[100000][2];


int main() {


	for (auto A : cts.cand_twosquares) {
		int64_t a = stoi(A.first);
		//if (a != 15487236) continue;
		//std::cout << "a=" << a << "\n";

		for (auto &B : cts.cand_twosquares) {
			int64_t b = stoi(B.first);
			if (b <= a)
				continue;
			//if (b != 51638427)	continue;

			ti = 0;
			for (auto& wx : A.second)
				for (auto& yz : B.second) {
					//T.push_back({ wx[0] * yz[0] + wx[1] * yz[1], abs(wx[0] * yz[1] - wx[1] * yz[0]) });
					//int64_t p = wx[0] * yz[0] + wx[1] * yz[1];
					//int64_t q = abs(wx[0] * yz[1] - wx[1] * yz[0]);
					T[ti++] = wx[0] * yz[0] + wx[1] * yz[1];
					T[ti++] = abs(wx[0] * yz[1] - wx[1] * yz[0]);
				
					//Ts[0][0] = p < q ? p : q;  // sort each pair
					//Ts[0][1] =  p < q ? q : p ;  // sort each pair


					T[ti++] = wx[0] * yz[1] + wx[1] * yz[0];
					T[ti++] = abs(wx[0] * yz[0] - wx[1] * yz[1]);
					//T.push_back({ wx[0] * yz[1] + wx[1] * yz[0], abs(wx[0] * yz[0] - wx[1] * yz[1]) });
				}
			//for (int i = 0; i < ti; i++) std::cout << T[i] << ", ";
			//std::cout << "\n";

			//std::cout << "a,b = " << a << "," << b << " ,"  "\n";
			//for (auto xy : T)
			//	std::cout << "   " << xy[0] << " " << xy[1] << "\n";

			//for (auto &xy : T) {
			for (int t = 0; t < ti; t += 2)
				for (auto i : { 0,1 }) {
					int64_t d = T[t + i];
					int64_t Area = T[t+ 1 - i] / 2;
					//if (Area == 4714211251386ull) std::cout << Area << " " << d << " (solution)\n";

					//std::cout << "d=" << d << "\n";
					if ((a * b - d) % 2 or a * b == d)
						continue;

					int64_t c2 = a * a + b * b - 2 * d;
					//std::cout << "c2 (-2d) = " << c2 << ", c=" << sqrt(c2) << "\n";
					if (c2 > b * b && is_square(c2)) {
						int64_t c = (int64_t)sqrt((long double)c2);
						int64_t Area = T[t + 1 - i] / 2;
						if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
							std::string Area_st = std::to_string(Area);
							if ( Area_st.find('0') == std::string::npos && Area_st.find('9') == std::string::npos)
							  std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
						}
					}
					c2 = a * a + b * b + 2 * d;
					//std::cout << "c2 (+2d) = " << c2 << ", c=" << sqrt(c2) << "\n";
					if (is_square(c2)) {
						int64_t c = (int64_t)sqrt((long double)c2);
						int64_t Area = T[t + 1 - i] / 2;
						if (cts.cand_twosquares.find(std::to_string(c)) != cts.cand_twosquares.end()) {
							std::string Area_st = std::to_string(Area);
							if (Area_st.find('0') == std::string::npos && Area_st.find('9') == std::string::npos)
								std::cout << "SOLUTION " << a << " " << b << " " << c << " " << Area << "\n";
						}
					}

				}
		}
		
	}
}
