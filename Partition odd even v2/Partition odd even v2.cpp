#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdio>
#include <algorithm>
#include <bitset>
#include "../Partition odd even/robin_hood.h"

// permutation algorithm from https://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation

static inline int __builtin_ctzll(unsigned long long x) {
	unsigned long ret;
	_BitScanForward64(&ret, x);
	return (int)ret;
}

uint64_t test1(int N, int R) {
	uint64_t count = 0;
	int64_t t;
	uint64_t perm = (1ull<<R) - 1;
	while (perm < (1ull<<N) ) {

		//std::cout << (std::bitset<64>)perm << std::endl;
		count++;

		t = perm | (perm - 1); // t gets v's least significant 0 bits set to 1
		// Next set to 1 the most significant bit to change, 
		// set to 0 the least significant ones, and add the necessary 1 bits.
		perm = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctzll(perm) + 1));
	}
	return count;
}

//std::unordered_map< uint64_t, std::vector<uint64_t> > total45map;
robin_hood::unordered_map< uint64_t, std::vector<uint64_t> >  total45map;

uint64_t target1 = 0, target2 = 0, target3 = 0, target4 = 0, target5 = 0;

// pre calculate fifth powers
uint64_t fifthpower[128];

void assess_candidate(uint64_t candidate) {
    uint64_t sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    for (int64_t i = 0; i < 64; i++)
        if (candidate & (1ULL << i)) {
            sum1 += i;
            sum2 += i * i;
            sum3 += i * i * i;
            sum4 += i * i * i * i;
        }

    if (sum1 == target1 && sum2 == target2 && sum3 == target3 && sum4 == target4) {
        printf(" **** SOLUTION **** %llu\n", candidate);
    }
}


int comb_even(uint64_t target5)
{
    int N = 32, K = 16;
    int64_t t;
    uint64_t perm = (1ull << K) - 1;

    int count = 0, match = 0;
    
    while (perm < (1ull << N)) {

        uint64_t evenbits = 0ULL;
        uint64_t  sum5 = 0, sum5plus1 = 0;
        // bit 0 -> 0, bit 1 -> 2, bit 31 -> 62
        // b has 16 set bits
        uint64_t bitmask = perm;
        int i = 0;
        while (bitmask) {
            if (bitmask%2) {
                evenbits |= (1ULL << i);
                sum5 += fifthpower[i];
                sum5plus1 += fifthpower[i + 1];
            }
            bitmask/=2;
            i += 2;
        }

        if (sum5plus1 % 32 == 0)
            if (total45map.find(sum5) != total45map.end()) {
                match++;
                for (auto oddbits : total45map[sum5]) {
                    uint64_t combined = evenbits | oddbits;
                    assess_candidate(combined);
                    //if (evenbits == 4702114326847508545ull)
                    //    std::cout << "oddbits: " << oddbits << ", evenbits: " << evenbits << std::endl;
                }
            }
        count++;
        if (count % 10000000 == 0) {
            std::cout << "comb_even count " << count / 1000000 << " million, matches: " << match << std::endl;
        }
        t = perm | (perm - 1); // t gets v's least significant 0 bits set to 1
        perm = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctzll(perm) + 1));

    } 

    return count;
}


int comb_odd(int batchsize) {
    int N = 31, K = 15;
    int64_t t;
    uint64_t perm = (1ull << K) - 1;
    uint64_t bitmask;

    int count = 0;
    while (perm < (1ull << N)) {
        uint64_t sum5 = 1, sum5p2 = 3*3*3*3*3;
        uint64_t oddbits = 1ULL << 1;
 
        int i = 3;
        bitmask = perm;
  
        while (bitmask) {
            if (bitmask%2) {
                oddbits |= (1ULL << i);
                sum5 += fifthpower[i];
                sum5p2 += fifthpower[i+2];
            }
            i+=2;
            bitmask /=2 ;
        }
        if (sum5 % 32 == 0 && sum5p2%32==0 )
            total45map[target5 - sum5].push_back(oddbits);

        //if (oddbits== 9370478457187893890ull)
        //    std::cout << "oddbits: " << oddbits << std::endl;

        count++;
        if (count % 10000000 == 0) {
            std::cout << "count " << count / 1000000 << " million, " ;
            std::cout << "total45map size " << total45map.size() << std::endl;
        }
        if (total45map.size() == 33000000) {
            comb_even(target5);
            total45map.clear();
        }
        t = perm | (perm - 1); // t gets v's least significant 0 bits set to 1
        perm = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctzll(perm) + 1));

    }

    comb_even(target5);
    return count;
}



int main()
{
    // expected totals and  fifth powers
    for (int64_t i = 0; i < 64; i++) {
        target1 += i;
        target2 += i * i;
        target3 += i * i * i;
        target4 += i * i * i * i;
        target5 += i * i * i * i*i;
    }
    for (int64_t i = 0; i <128; i++) 
        fifthpower[i] = i * i * i * i * i;
    target1 /= 2;
    target2 /= 2;
    target3 /= 2;
    target4 /= 2;
    target5 /= 2;
    std::cout << "target5 " << target5 << std::endl;

    int batchsize = 35000000;
    total45map.reserve(batchsize + 1);

    // expecting 31c15 = 300,540,195
    std::cout << comb_odd(batchsize) << std::endl;
}
