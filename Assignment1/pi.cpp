/*H**********************************************************************
* FILENAME :        main.cpp         
*
* DESCRIPTION :
*       Generateing pi to 30 precision.
*
* NOTES :
*   Code adapted from https://crypto.stanford.edu/pbc/notes/pi/code.html
*   Euler's Convergence Improvements
*   every 14 terms gives 4 digits, thus the magnifying factor is pow(10, 4)
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :   13 Feb 2019
*
*H*/



#include <stdio.h>

#define MAGNIFYING_FACTOR 10000
#define PRECISION 120

int main() {
    int pi[PRECISION];
    int carry = 0;

    for (int i = 0; i < PRECISION; i++) pi[i] = 2;

    for (int k = PRECISION; k > 0; k -= 14) {
        int sum = 0;

        for(int i = k; i > 0; --i){
            sum = sum * i + pi[i] * MAGNIFYING_FACTOR; //numerator accumulate
            int denom = 2*i-1;
            pi[i] = sum % denom;
            sum /= denom;
        }

        printf("%.4d ", carry + sum / MAGNIFYING_FACTOR);
        carry = sum % MAGNIFYING_FACTOR;
    }
    printf("\n");
    return 0;
}