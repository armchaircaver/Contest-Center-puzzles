#pragma once
#include <cstdint>
#include <vector>

struct pythagTriple { uint64_t a; uint64_t b; uint64_t c; };

class Ppt {
    struct hisStruc { uint64_t a; uint64_t b; uint64_t c; uint64_t t; };
    uint64_t LIM = 1000;
    int i = 0;
 
    // depth needed is approx 0.7 * sqrt( max hypotenuse )
    // so depth 1000000 should be OK for hypotenuse up to approx 2*10^12 (which would take a few hours to run)
    hisStruc* history = new hisStruc[1000000];


public:
    Ppt(uint64_t lim) {
        LIM = lim;

        history[0] = { 3,4,5,0 };
        i = 0;
     }

    int maxDepth() {
        int depth = 0;
        for (int i = 0; history[i].c > 0; i++) { depth++; }
        return depth;
    }

    pythagTriple first(){
        return { 3,4,5 };
    }

    pythagTriple next() {
        uint64_t na, nb, nc;

        while (true) {
 
            if (history[i].t >= 3) {
                //# back up one level unless at top level
                if (i == 0)
                    return { 0,0,0 };
                i--;
            }

            else {
                uint64_t a = history[i].a;
                uint64_t b = history[i].b;
                uint64_t c = history[i].c;
                //printf("i=%d  a,b,c = %llu,%llu,%llu, t=%llu\n", i, a, b, c, history[i].t);

                if ((history[i].t == 0) && (3 * c - 2 * abs((int64_t)a - (int64_t)b) > LIM)) {
                    // all three subbranches would exceed max hypotenuse
                    history[i].t = 3;
                    continue;
                }
                history[i].t++;
                //printf("a. history[%d]=%llu,%llu,%llu, t=%llu\n", i, history[i].a, history[i].b, history[i].c, history[i].t);
                uint64_t t = history[i].t;

                if (t == 1) {
                    nc = 2 * a - 2 * b + 3 * c;
                    if (nc > LIM)
                        continue;
                    i++;
                    na = a - 2 * b + 2 * c;
                    nb = 2 * a - b + 2 * c;
                    history[i] = { na, nb, nc, 0 };
                    //print "c. history[{}]=".format(i), history[i]
                    return { na, nb, nc };
                }
                else if (t == 2) {
                    nc = 2 * b - 2 * a + 3 * c;
                    if (nc > LIM) {
                        history[i].t = 3;
                        continue;
                    }
 
                    i++;
                    na = 2 * b - a + 2 * c;
                    nb = b - 2 * a + 2 * c;
                    history[i] = { na, nb, nc, 0 };
                    //print "g. history[{}]=".format(i), history[i]
                    return { na, nb, nc };
                }
                else if (t == 3) {
                    nc = 2 * a + 2 * b + 3 * c;
                    if (nc > LIM)
                        continue;
                    i++;
                    na = a + 2 * b + 2 * c;
                    nb = 2 * a + b + 2 * c;
                    history[i] = { na, nb, nc, 0 };
                    //print "e. history[{}]=".format(i), history[i]
                    return { na, nb, nc };
                }
                else {
                    printf("unexpected value in pptClassBerggren, t=%llu\n", t);
                    exit(1);
                }
            }
        }
    }
};

