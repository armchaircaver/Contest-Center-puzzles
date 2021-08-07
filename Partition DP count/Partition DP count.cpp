#include <iostream>
#include <vector>
#include <stdint.h>
#include <bitset>
#include <cstdio>
#include <algorithm>
#include <random>

std::vector<int> arr;

std::vector<std::vector<int64_t>> count;
int target;
int64_t target1=0, target2=0, target3=0, target4=0, target5=0;

int64_t countSubsetsWithSumEqualToGivenSum(std::vector<int>& arr, int sum) {
    if (arr.size() == 0 || sum <= 0) {
        return 0;
    }

    int n = (int)arr.size();

    for (int i = 0; i < arr.size(); i++) {
        std::vector<int64_t> v;
        v.resize(sum + 1);
        count.push_back(v);
    }

    for (int i = 0; i < n; i++) {
        count[i][0] = 1;
    }

    for (int j = 0; j <= sum; j++) {
        if (arr[0] == j) {
            count[0][j] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= sum; j++) {

            int64_t includingCurrentValue = 0;
            int64_t excludingCurrentValue = 0;

            if (arr[i] <= j) {
                includingCurrentValue = count[i - 1][j - arr[i]];
            }

            excludingCurrentValue = count[i - 1][j];

            count[i][j] = includingCurrentValue + excludingCurrentValue;
        }
    }
    return count[n - 1][sum];
}

void printsubset(uint64_t bitmask) {
    printf("Solution: ");
    for (int i = 0; i < 64; i++) 
        if (bitmask & (1ULL << i)) 
           printf("%d, ", arr[i]);
    printf("\n");
}

int tested = 0;

void examinesubset(uint64_t bitmask) {
    tested++;
    if (tested % 10000000 == 0) {
        printf("%d candidates tested\n", tested);
        std::cout << std::bitset<64>(bitmask) << std::endl;
    }

    if (std::bitset<64>(bitmask).count() != 32)
        return;

    int total1 = 0;
    int total3 = 0;
    for (int i = 0; i < 64; i++) {
        if (bitmask & (1ULL << i)) {
            //printf("%d, ", arr[i]);
            total3 += arr[i];
            total1 += i+1;
        }
    }
    if (total1 == target1) {
        //std::cout << std::bitset<64>(bitmask) << std::endl;
        //printf("  total3=%d\n", total3);
        if (total3 != target) {
            printf("examine: masmatch total3=%d, target=%d, exiting\n", total3, target);
            exit(1);
        }

 
        int64_t total2 = 0;
        int64_t total3a = 0;
        int64_t total4 = 0;
        int64_t total5 = 0;
        for (int64_t i = 0; i < 64; i++) {
            if (bitmask & (1ULL << i)) {
                int64_t n = i + 1;
                total2 += n * n;
                total3a += n * n * n;
                total4 += n * n *n * n;
                total5 += n * n*n*n*n;
            }
        }
        printf("totals %d, %lld, %lld, %lld, %lld\n", total1, total2, total3a, total4, total5);
        if (total3a != target3) {
            printf("examine: masmatch total3a=%lld, target3=%lld, exiting\n", total3a, target3);
            exit(1);
        }
        if (total2 == target2 && total4 == target4 /* && total5 == target5*/) {
            printf("*****SOLUTION***** (rebased to 5-68)\n");
            for (int i = 0; i < 64; i++) 
                if (bitmask & (1ULL << i)) 
                    printf("%d, ", i+5);
            printf("\n");
        }
    }
}

void backtrack2(int subtotal, int i, uint64_t bitmask, int depth) {
    /*
    printf("backtrack2 , subtotal=%d, i=%d, arr[i]=%d, depth=%d\n", subtotal, i, arr[i], depth);
    for (int j = 0; j < count.size(); j++)
        printf("%lld,", count[j][subtotal]);
    printf("\n");
    */

    if (subtotal == 0) {
        printsubset(bitmask);
       // examinesubset(bitmask);
        //record(bitmask);
        return;
    }

    while (i > 0 && count[i][subtotal] > 0) {

        // are we at the top of a step
        if (count[i - 1][subtotal] < count[i][subtotal])
            backtrack2(subtotal - arr[i], i - 1, bitmask | (1ULL << i), depth + 1);
        i--;
    }
    if (i==0 && count[i][subtotal] > 0)
        backtrack2( subtotal - arr[i], i - 1, bitmask | (1ULL << i), depth + 1);
}

void test1() {
    int total = 0;
    arr.clear();
    for (int i = 1; i <= 8; i++) {
        arr.push_back(i);
        total += i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
    for (int j = 0; j < arr.size(); j++)
        printf("%d,", arr[j]);

    int target = 18;
    printf("\ntotal=%d, target=%d\n", total, target);

    int64_t c = countSubsetsWithSumEqualToGivenSum(arr, target);
    printf("count = %lld, last column of count:\n", c);
    for (int j = 0; j < count.size(); j++)
        printf("%lld,", count[j][target]);
    printf("\n");

    for (int i = 0; i < count.size(); i++) {
        for (int j = 0; j <= target; j++)
            printf("%lld,", count[i][j]);
        printf("\n");
    }
    backtrack2(target, (int)arr.size() - 1, 0ULL, 0);

}

void contestcen_partition() {
    arr.clear();

    //arr = { 2, 3, 7, 1, 4, 5 };
    //int target = 7;

    for (int64_t i = 1; i <= 64; i++) {
        target1 += i;
        target2 += i * i;
        target3 += i * i * i;
        target4 += i * i * i * i;
        target5 += i * i * i * i * i;
    }
    target1 /= 2;
    target2 /= 2;
    target3 /= 2;
    target4 /= 2;
    target5 /= 2;
    printf("targets: %lld %lld %lld %lld %lld \n", target1, target2, target3, target4, target5);

    arr.clear();
    int total = 0;
    for (int i = 1; i <= 64; i++) {
        arr.push_back(i*i*i);
        total += i*i*i;
    }
    target = total / 2;
    printf("total=%d, target=%d\n", total, target);

    int64_t c = countSubsetsWithSumEqualToGivenSum(arr, target);
    printf("count = %lld, last column of count:\n", c);
    for (int j = 0; j < count.size(); j++)
        printf("%lld,", count[j][target]);
    printf("\n");

    backtrack2(target, (int)arr.size() - 1, 0ULL, 0);

}

int main() {
    //test1();
    contestcen_partition();
 }

