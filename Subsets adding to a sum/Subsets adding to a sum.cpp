// https://stackoverflow.com/questions/4632322/finding-all-possible-combinations-of-numbers-to-reach-a-given-sum

#include <iostream>
#include <vector>
#include "../Pythag/Timer.h" 

// declare these globlally to minimise parameters passed in recursive routine (even though we can pass them by reference)
std::vector<int64_t> numbers;
std::vector<int64_t> partial;

void subset_sum_recursive(
    int startpos,
    int64_t target,
    int64_t partialsum){

    if (partialsum == target) {
        std::cout << "sum([";
        for (auto i : partial) std::cout << i << ",";
        std::cout << "])=" << target << " (" << partial.size()<<" items)" << std::endl;
    }

    if (partialsum >= target)
        return;

    if (2 * partial.size() > numbers.size())
        return;

    partial.push_back(0);
    int lastpos = partial.size() - 1;
    for (int i = startpos; i != numbers.size(); i++) {
        partial[lastpos] = numbers[i];
        subset_sum_recursive( i+1, target, partialsum+numbers[i]);
     }
    partial.pop_back();

}

void subset_sum(std::vector<int64_t> & a, int64_t target){
    partial.clear();
    numbers = a;
    subset_sum_recursive( 0, target,  0);
}


int main(){

    std::vector<int64_t> a = { 3,9,8,4,5,7,10 };
    int64_t n = 15;
    //std::cin >> n;
    subset_sum(a, n);

    std::vector<int64_t> b;
    int64_t half=0;
    for (int64_t i = 0; i <32; i++) {
        int64_t m =  i* i* i* i* i;
        half += m;
        b.push_back(m);
    }
    half /= 2;
    std::cout << "half = " << half << std::endl;
    Timer tim;
    tim.start();
    subset_sum(b, half);
    tim.end();
    printf("%lld ms\n", tim.ms());

    return 0;
}