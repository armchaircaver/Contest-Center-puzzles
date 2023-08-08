#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

std::vector<uint64_t> pan;
std::vector<uint64_t> pansquared;
std::unordered_set<uint64_t> pansquared_set;

int64_t isqrt(int64_t x) {
    int64_t q = 1, r = 0;
    while (q <= x) {
        q <<= 2;
    }
    while (q > 1) {
        int64_t t;
        q >>= 2;
        t = x - r - q;
        r >>= 1;
        if (t >= 0) {
            x = t;
            r += q;
        }
    }
    return r;
}


void generate_pandigital() {
    std::string s = "0123456789";

    do {
        uint64_t n = stoull(s);
        if (n > 1000000000) {
            pan.push_back(n);
            pansquared.push_back( (n/9)*(n/9) );
            pansquared_set.insert((n / 9) * (n / 9));
        }
    }
    while (std::next_permutation(s.begin(), s.end()));
}

__declspec(noinline) void search_lower() {
    for (auto a : pansquared) {
        for (auto b : pansquared) {
            if (pansquared_set.find(a + b) != pansquared_set.end()) {
                std::cout << isqrt(a) * 9 << ", " << isqrt(b) * 9 << "\n";
                return;
            }
        }
        std::cout << "searched a = " << a << ", " << isqrt(a)*9 << "\n";
    }
}


int main()
{
    generate_pandigital();
    search_lower();

  }