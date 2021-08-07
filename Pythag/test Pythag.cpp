#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "pptClassberggren.h"
//#include "pptClass.h"
#include "Timer.h"

int main(int argc, char** argv){

	uint64_t hlim = 1000;
	if (argc >= 2)
		hlim = atoll(argv[1]);

	Ppt p = Ppt(hlim);
	uint64_t count = 0;
	Timer tim;
	tim.start();
	for (pythagTriple t = p.first(); t.a > 0; t = p.next()) {
		//printf("a=%llu, b=%llu, c=%llu\n", t.a, t.b, t.c);
		count++;
	}
	tim.end();
	printf("%llu pythagorean triples in %llu ms\n", count, tim.ms() );
	printf("max depth = %d\n", p.maxDepth());

}