// Code adapted from https://crypto.stanford.edu/pbc/notes/pi/code.html

#include <stdio.h>
#include <cmath>
#define PRECISION 106

void stanford_pi(){
	int r[PRECISION];
    int i, k;
    int b, d;
    int c = 0;

    //Initialization
    for (i = 0; i < PRECISION; i++) r[i] = 2000;
    

    for (k = PRECISION; k > 0; k -= 14) {
        d = 0;

        i = k;
        while(1) {
            d += r[i] * 10000;
            b = 2 * i - 1;

            r[i] = d % b;
            d /= b;
            i--;
            if (i == 0) break;
            d *= i;
        }
        printf("%.4d", c + d / 10000);
        c = d % 10000;
    }
    printf("\n");
}



int main() {
    my_pi();
    return 0;
}