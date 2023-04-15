#include "func.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int x;
    float a, b;
    int c, d;
    
    for (;;) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%f %f", &a, &b);
            float res = Derivative(a, b);
            printf("%f\n", res);
            x = 0;
        } else if (x == 2) {
            scanf("%d %d", &c, &d);
            int res = GCF(c, d);
            printf("%d\n", res);
            x = 0;
        } else {
            break;
        }
    }
    return 0;
}