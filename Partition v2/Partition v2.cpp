/*
Partition (Based on a problem from Paul Cleary)
How can the set of consecutive integers from 5 through 68 be partitioned into two equal-sized
subsets whose sums, sums of squares, sums of cubes, sums of fourth powers and sums of fifth
powers are all equal?
 */

 /*
 Treat the problem as a set of conecutive integers -31..+32.
 First, find a subset of less that 32 items with sum of fifth powers is 32^5 / 2 = 2^24 = 16777216
 and check that sum of 1st powers  is 31^1/2=16 and  3rd powers is 32^3/2 = 16384
 */
using namespace std;

#include <iostream>
#include <vector>
#include <stdio.h> 
#include <stdlib.h> 

// sum from end of list backwards
int64_t backsum[5][64] = { 0 };


// prints subset found 
void printSubset(int64_t A[], int64_t size) {
	printf("\n");
	for (int64_t i = 0; i < size; i++)
		printf("%lld ", A[i]);
	printf(" (%lld items)\n", size);
}

void checkfurther(int64_t running_subset[64], int64_t size, int64_t target_sum[5]) {
	int64_t s[5] = { 0 };

	for (int64_t i = 0; i < size; i++) {
		int64_t n = running_subset[i];
		for (int k = 0; k < 5; k++)
		{
			s[k] += n;
			n *= running_subset[i];
		}
	}

	int matches = 0;
	for (int k = 0; k < 5; k++)
		if (s[k] == target_sum[k])
			matches++;

	if (matches >= 0) {
		//printf("***** Strong candidate *****\n");
		for (int k = 0; k < 5; k++)
			printf("%lld v. %lld\n", s[k], target_sum[k]);
	}
}


// inputs 
// s		 - set vector 
// t		 - tuplet vector 
// s_size	 - set size 
// t_size	 - tuplet size so far 
// sum		 - sum so far 
// ite		 - nodes count 
// target_sum - sum to be found 


void subset_sum(int64_t weights[5][64], int64_t running_subset[64],
	int w_size, int rs_size,
	int64_t running_sums[5], int ite,
	int64_t  target_sum[5])
{
	const int max_size = 32;

	if (rs_size > max_size)
		return;
	if (running_sums[1] > target_sum[1])
		return;
	if (running_sums[3] > target_sum[3])
		return;

	//is this a feasible subset
	if ((rs_size < max_size)) {
		for (int k = 0; k < 5; k++)
			if (running_sums[k] + backsum[k][max_size - rs_size - 1] < target_sum[k])
				return;
	}
	printSubset(running_subset, rs_size);

	printf("running sums: ");
	for (int k = 0; k < 5; k++) printf("%lld ", running_sums[k]);
	printf("\n");

	checkfurther(running_subset, rs_size, target_sum);
	//printf("sum = %lld, backsum[max_size - t_size1-] = %lld\n", sum, backsum[max_size - t_size-1]);

	if (target_sum[4] == running_sums[4])
	{
		// We found sum 
		checkfurther(running_subset, rs_size, target_sum);
	}

	int64_t nextrunning_sums[5];

	for (int i = ite; i < w_size; i++) {
		running_subset[rs_size] = weights[0][i];
		for (int k = 0; k < 5; k++)
			nextrunning_sums[k] = running_sums[k] + weights[k][i];

		// consider next level node (along depth) 
		subset_sum(weights, running_subset, w_size, rs_size + 1, nextrunning_sums, i + 1, target_sum);
	}
}


int main() {
	int64_t weights[5][64];

	int64_t s[5] = { 0 };

	for (int64_t i = 0; i <64;i++) {
		int64_t n = i;
		weights[0][i] = n ;
		weights[1][i] = n * n ;
		weights[2][i] = n * n * n ;
		weights[3][i] = n * n * n * n ;
		weights[4][i] = n * n * n * n * n;
	}

	for (int k = 0; k < 5; k++) {
		backsum[k][0] = weights[k][63];
		for (int i = 1; i < 64; i++)
			backsum[k][i] = backsum[k][i - 1] + weights[k][63 - i];
	}
	int64_t target[5] = { 0 };
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < 64; i++)
			target[k] += weights[k][i];
		target[k] /=2;
		printf("%lld ", target[k]);
	}
	printf("\n");

	int64_t running_subset[64];
	int64_t running_sums[5] = { 0 };
	subset_sum(weights, running_subset, 64, 0, running_sums, 0, target);
		
	return 0;
}

