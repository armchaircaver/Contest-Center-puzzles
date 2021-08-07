#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdio>
#include <algorithm>
#include "robin_hood.h"

//std::unordered_map< uint64_t, std::vector<uint64_t> > total45map;
robin_hood::unordered_map< uint64_t, std::vector<uint64_t> >  total45map;

uint64_t target1 = 0, target2 = 0, target3 = 0, target4= 0, target5 = 0 ;

// pre calculate fifth powers
uint64_t fifthpower[65];

bool assess_candidate(uint64_t candidate) {
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
        return true;
    }
    return false;
}


int comb_even(uint64_t target5)
{
    int N = 32, K = 16;
    std::vector<int> bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    int count = 0, match = 0;
    do {
        uint64_t evenbits = 0ULL;
        uint64_t  sum5 = 0, sum5plus1 = 0;

        // bit 0 -> 0, bit 1 -> 2, bit 31 -> 62
        // b has 16 set bits
        for (int i = 0; i < 32; ++i)
            if (bitmask[i]) {
                evenbits |= (1ULL << (2 * i));
                sum5 += fifthpower[2 * i];
                sum5plus1 += fifthpower[2 * i + 1];
            }
 
        if (sum5plus1 % 32 == 0)
            if (total45map.find(sum5) != total45map.end()) {
                match++;
                for (auto oddbits : total45map[sum5]) {
                    uint64_t combined = evenbits | oddbits;
                    if (assess_candidate(combined)) {
                        std::cout << "oddbits: " << oddbits << ", evenbits: " << evenbits << std::endl;
                    }
                }
            }
        count++;
        if (count % 10000000 == 0) {
            std::cout << "comb_even count " << count / 1000000 << " million, matches: " << match << std::endl;
        }
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return count;
}


int comb_odd(int batchsize) {
    int N = 31, K = 15;
    std::vector<int> bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    int count = 0;
    do {
         uint64_t sum5 = 1; 
        uint64_t oddbits = 1ULL << 1;
        // bit 0 -> 3, bit 1 ->5, bit 30 -> 63
        // b has 15 set bits
        /*
        for (int i = 0; i < 31; ++i)
            if (bitmask[i]) {
                oddbits |= (1ULL << (2 * i + 3));
                sum5 += fifthpower[2 * i + 3];
            }
        */
        int i = 0;
        for (auto b : bitmask) {
            if (b) {
                oddbits |= (1ULL << (2 * i + 3));
                sum5 += fifthpower[2 * i + 3];
            }
            i++ ;
        }
        if ( sum5%32 == 0)
          total45map[target5 - sum5].push_back(oddbits);

        count++;
        if (count % 10000000 == 0) {
            std::cout << "count " << count/1000000 <<" million"<< std::endl;
            std::cout << "total45map size " << total45map.size() << std::endl;
        }
        if (total45map.size() == 33000000) {
            comb_even(target5);
            total45map.clear();
        }

    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    comb_even(target5);
    return count;
}



int main()
{
    // expected totals and  fifth powers
    for (int64_t i = 0; i < 64; i++) {
        fifthpower[i] = i * i * i * i * i;
        target1 += i;
        target2 += i * i;
        target3 += i * i * i;
        target4 += i * i * i * i;
        target5 += fifthpower[i];
    }
    fifthpower[64] = 1ULL << (6 * 5);
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
