#include <iostream>
#include <vector>
#include <stdio.h> 
#include <stdlib.h> 

int64_t diffs[31];
int64_t a[32] = { 0 };
int diffcount[6] = { 0 };

const int64_t t2 = 42672;
const int64_t t3 = 2032128;
const int64_t t4 = 103223568;
const int64_t t5 = 5461682688;
int64_t count = 0;

void examine() {
	/*
	for (int i = 0; i < 32; i++)
		printf("%lld ", a[i]);
	printf("\n");
	*/
	count++;
	if (count % 1000000 == 0)
		printf("%lld\n", count);

	int64_t s2 = 0;
	int64_t s3 = 0;
	int64_t s4 = 0;
	int64_t s5 = 0;
	for (int i = 0; i < 32; i++) {
		int64_t n = a[i];
			s2 += n * n;
		s3 += n * n*n;
		s4 += n * n*n*n;
		s5 += n * n*n*n*n;
		}
	if (s2 == t2 && s3 == t3 && s4 == t4 && s5 == t5) {
		printf("solution\n");
		for (int i = 0; i < 32; i++)
			printf("%lld ", a[i]);
		printf("\n");
	}
}

void search(int depth, int64_t lastdiff, int64_t subtotal) {

	/*
	printf("depth=%d subtotal=%lld : ", depth, subtotal);
	for (int i = 0; i < 32; i++)
		printf("%lld ", a[i]);
	printf("\n");
	*/
	for (int64_t i : { 1, 2, 3 }) {
		//if (i == lastdiff)
		//	continue;
		if (diffcount[i] == 12)
			continue;
		a[depth] = a[depth - 1] + i;
		diffcount[i]++;
		if (depth == 31 && subtotal+ a[depth]==1008)
			examine();

		if (depth < 31)
			search(depth + 1, i, subtotal + a[depth]);
		diffcount[i]--;

	}
}

int main() {
	search(1, -1, 0);
}