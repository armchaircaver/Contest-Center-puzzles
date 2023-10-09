#include <map>
#include "../is_square/is_square.h"
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

int ti = 0;

std::array<std::array<int64_t, 2>,100000> Tset;

void print_time() {
	time_t my_time = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &my_time);
	printf("%s \n", str);
}

int main() {

	print_time();

	//std::unordered_set<int64_t> C2s;
	//absl::flat_hash_set<int64_t> C2s;
	robin_hood::unordered_set<int64_t> C2s;

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
			if (b <= a)
				continue;
			//if (b != 51638427)	continue;

			ti = 0;
			for (auto& wx : A.second)
				for (auto& yz : B.second) {

					int64_t p = wx[0] * yz[0] + wx[1] * yz[1];
					int64_t q = abs(wx[0] * yz[1] - wx[1] * yz[0]);
					Tset[ti++] = { p < q ? p : q ,p < q ? q : p };

					p = wx[0] * yz[1] + wx[1] * yz[0];
					q = abs(wx[0] * yz[0] - wx[1] * yz[1]);
					Tset[ti++] = { p < q ? p : q ,p < q ? q : p };
				}

			//std::sort(Tset.begin(), Tset.begin() + ti);

			for (int t = 0; t < ti; t++) {
				//if (t > 0 && Tset[t - 1] == Tset[t]) 	continue;
				for (auto i : { 0,1 }) {


					int64_t d = Tset[t][i];
					// if Tset[t][1 - i] is 2*Area, then i is divisible by 12, as area is divisible by 6
					if (Tset[t][1 - i] % 12 ) 
						continue;
					int64_t Area = Tset[t][1 - i] / 2;
					
					// look at https://stackoverflow.com/questions/4351371/c-performance-challenge-integer-to-stdstring-conversion
										

					//if (Area == 4714211251386ull) std::cout << Area << " " << d << " (solution)\n";

					//std::cout << "d=" << d << "\n";
					if ((a * b - d) % 2 or a * b == d)
						continue;

					int64_t c2 = a * a + b * b - 2 * d;
					//std::cout << "c2 (-2d) = " << c2 << ", c=" << sqrt(c2) << "\n";
					if (c2 > b * b && C2s.find(c2) != C2s.end() ) {
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
					if ( C2s.find(c2) != C2s.end() ) {
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
