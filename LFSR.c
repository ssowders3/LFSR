#include <stdio.h>
#include <math.h>
#include <string.h>
#define M (int) pow(2,24)
#define NUM_TOSS 10000
#define A 0x43FD43FD
#define C 0xC39EC3
unsigned int lfsr = 115;
unsigned int lcg = 115;
int findMode(char*);
void piEstimator(char*);
int numH(int, int*);
double LFSR();
double LCG();


int main() {
    static int flip[NUM_TOSS];
    printf("\n--------------------------\n");
    for (int j = 0; j < NUM_TOSS; j++) {
        flip[j] = findMode("LCG");
    }
    for (int i = 1; i < 26; i++) {
        printf("Length: %d num of heads: %d\n", i, numH(i, flip));
    }
    printf("\n--------------------------\n");
    for (int j = 0; j < NUM_TOSS; j++) {
        flip[j] = findMode("LFSR");
    }
    for (int i = 1; i < 26; i++) {
        printf("Length: %d num of heads: %d\n", i, numH(i, flip));
    }
    printf("\nEstimate Pi: LFSR\n");
    piEstimator("LFSR");
    printf("\nEstimate Pi: LCG\n");
    piEstimator("LCG");
    printf("\nRandom nums: LFSR\n");
    for (int i = 0 ; i < 10; i++) {
        printf("%f\n", LFSR());
    }
    printf("\nRandom nums: LCG\n");
    for (int i = 0 ; i < 10; i++) {
        printf("%f\n", LCG() );
    }
}
double LCG() {
    lcg = (A * lcg + C) % M;
    lcg = lcg % (int) pow(2,24);
    return lcg/pow(2,24);
}
double LFSR() {
    int bit23 = lfsr >> 23;
    int bit22 = lfsr >> 22;
    int bit21 = lfsr >> 21;
    int bit16 = lfsr >> 16;
    int XOR = bit23 ^ bit22 ^ bit21 ^ bit16;
    int Xand = XOR & 1;
    //System.out.println(Xand);
    lfsr = (lfsr << 1) | Xand;
    lfsr = lfsr % (int) pow(2,24);
    return lfsr/pow(2,24);

}
int findMode(char* ptr) {
    if (strcmp(ptr, "LFSR") == 0) {
        return (int) round(LFSR());
    }
    if (strcmp(ptr, "LCG") == 0) {
        return (int) round(LCG());
    }
    //need return
    return -1;
}
int numH(int length, int *flip) {
    int count = 0;
    int heads = 0;
    int boolF = 0;
    for (int i = 0; i < NUM_TOSS; i++) {
        if (flip[i]) {
            heads++;
            if (boolF) {
                boolF = 0;
            }
        } else {
            heads = 0;
            if (boolF) {
                count++;
                boolF = 0;
            }
        }
        if (heads == length) {
            boolF = 1;
            if (i == NUM_TOSS - 1) {
                count++;
                //System.out.println(count);
            }
        }
    }
    return count;
}
void piEstimator(char* ptr) {
    long z = 0, n = 0;
    double x, y, pi;
    for (int j = 0; j < 10; j++) {
        z = 0;
        n += 10000;
        for (long i = 0; i < n; i++) {
            if (strcmp(ptr, "LCG") == 0) {
                x = LCG();
                y = LCG();
            } else if (strcmp(ptr, "LFSR") == 0) {
                x = LFSR();
                y = LFSR();
            } else {
                return;
            }
            if (sqrt(x*x + y*y) <= 1) {
                z++;
            }
        }
        pi = 4.0*z/n;
        printf("Pi is estimated to be %f\n" , pi);
    }
}
