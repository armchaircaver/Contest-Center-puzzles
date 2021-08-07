/*
Partition (Based on a problem from Paul Cleary)
How can the set of consecutive integers from 5 through 68 be partitioned into two equal-sized 
subsets whose sums, sums of squares, sums of cubes, sums of fourth powers and sums of fifth 
powers are all equal? 
 */

/*
Treat the problem as a set of conecutive integers -31..+32.
First, find a subset of less that 32 items with sum of fifth powers is 32^5 / 2 = 2^24 = 16777216
and check that sum of 1st powers  is 16 and  3rd powers is 32^3/2 = 16384
*/
using namespace std;

#include <iostream>
#include <vector>
#include <stdio.h> 
#include <stdlib.h> 
#include <unordered_map>


#define ARRAYSIZE(a) (sizeof(a))/(sizeof(a[0])) 

static int64_t total_nodes;
int64_t maxweight = 0;
std::unordered_map<int64_t, int64_t> fifthroot;

// sum from end of list backwards
int64_t backsum[64] = { 0 };


// prints subset found 
void printSubset(int64_t A[], int64_t size){
	printf("\n");
	for (int64_t i = 0; i < size; i++)
		printf("%lld ", A[i]);
		printf(" (%lld items)\n",size);
}

void checkfurther(int64_t A[], int64_t size) {
	int64_t s1 = 0;
	int64_t s2 = 0; 
	int64_t s3 = 0;
	int64_t s4 = 0;
	int64_t s5 = 0;
	int64_t t1 = 0;
	int64_t t2 = 0;
	int64_t t3 = 0;
	int64_t t4 = 0;
	int64_t t5 = 0;

	for (int64_t i = 0; i < size; i++) {
		int64_t n = fifthroot[A[i]];
		s1 += n;
		s2 += n * n;
		s3 += n * n * n;
		s4 += n * n * n * n;
		s5 += n * n * n * n * n;
	}
	for (int64_t n = -31; n <=32; n++) {
		t1 += n;
		t2 += n * n;
		t3 += n * n * n;
		t4 += n * n * n * n;
		t5 += n * n * n * n*n;
	}
	if (s1 * 2 == t1 &&  s3 * 2 == t3 )
		printf("***** Strong candidate *****\n");
	printf("%lld v. %lld\n", s1 * 2, t1);
	printf("%lld v. %lld\n", s2 * 2, t2);
	printf("%lld v. %lld\n", s3 * 2, t3);
	printf("%lld v. %lld\n", s4 * 2, t4);
	printf("%lld v. %lld\n", s5 * 2, t5);
}


// inputs 
// s		 - set vector 
// t		 - tuplet vector 
// s_size	 - set size 
// t_size	 - tuplet size so far 
// sum		 - sum so far 
// ite		 - nodes count 
// target_sum - sum to be found 


void subset_sum(int64_t s[], int64_t t[],
	int64_t s_size, int64_t t_size,
	int64_t sum, int ite,
	int64_t const target_sum)
{
	total_nodes++;

	int max_size = 22;
	if (t_size > max_size)
		return;
	//is this a feasible subset
	if ((t_size < max_size) && (sum + backsum[max_size - t_size-1] < target_sum))
		return;

	//printSubset(t, t_size);
	//printf("sum = %lld, backsum[max_size - t_size1-] = %lld\n", sum, backsum[max_size - t_size-1]);

	if (target_sum == sum)
	{
		// We found sum 
		printSubset(t, t_size);
		checkfurther(t, t_size);

		// constraint check 
		if (ite + 1 < s_size && sum - s[ite] + s[ite + 1] <= target_sum)
		{
			// Exclude previous added item and consider next candidate 
			subset_sum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
		}
		return;
	}
	else
	{
		// constraint check 
		if (ite < s_size && sum + s[ite] <= target_sum)
		{
			// generate nodes along the breadth 
			for (int i = ite; i < s_size; i++)
			{
				t[t_size] = s[i];

				if (sum + s[i] <= target_sum) {
					// consider next level node (along depth) 
					subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
				}
			}
		}
	}
}

// Wrapper that prints subsets that sum to target_sum 
void generateSubsets(int64_t s[], int64_t size, int64_t target_sum)
{
	int64_t* tuplet_vector = (int64_t*)malloc(size * sizeof(int64_t));

	int64_t total = 0;
	for (int i = 0; i < size; i++)
		total += s[i];

	if (s[0] <= target_sum && total >= target_sum)
		subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);

	free(tuplet_vector);

}

int main(){
	int64_t weights[64] = {0};

	for (int64_t n = -31; n <= 32; n++)
		fifthroot[n * n * n * n * n] = n;

	int64_t n;
	int64_t s = 0;
	for (int i = 0; i < 64; i++) {
		n = i - 31;
		weights[i] = n*n*n*n*n;
		printf("%lld ", weights[i]);
		s += weights[i];
	}
	maxweight = weights[63];

	backsum[0] = weights[63];
	for (int i = 1; i < 64; i++)
		backsum[i] = backsum[i - 1] + weights[63 - i];

	int64_t target = 16777216;
	printf("\n target=%lld\n", target);

	int64_t size = ARRAYSIZE(weights);

	generateSubsets(weights, size, target);

	printf("\nNodes generated %lld\n", total_nodes);

	return 0;
}

