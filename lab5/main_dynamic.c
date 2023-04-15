#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <math.h>
#include <stdbool.h>

const char LIB1[] = "./libd1_dynamic.so";
const char LIB2[] = "./libd2_dynamic.so";

int main(int argc, char* argv[]) {
    void *library;
    bool flag = false;
    int x, c, d;
    double a, b;

    library = dlopen(LIB2, RTLD_LAZY);
    if (!library) {
        printf("Error dlopen(): %s\n", dlerror());
        return 1;
    }

    double(*Derivative)(double x, double y);
    int(*GCF)(int x, int y);
    *(void**)(&Derivative) = dlsym(library, "Derivative");
    *(void**)(&GCF) = dlsym(library, "GCF");

    for (;;) {
        scanf("%d", &x);
        if (x == 0) {
            dlclose(library);
            if (flag) {
                library = dlopen(LIB2, RTLD_LAZY);
                flag = false;
            } else {
                library = dlopen(LIB1, RTLD_LAZY);
                flag = true;
            }
            if (!library) {
                printf("Error dlopen(): %s\n", dlerror());
                return 1;
            }
            *(void**)(&Derivative) = dlsym(library, "Derivative");
            *(void**)(&GCF) = dlsym(library, "GCF");
        } else if (x == 1) {
            scanf("%lf %lf", &a, &b);
            printf("Result: ");
            double res = Derivative(a, b);
            printf("%lf\n", res);
        } else if (x == 2) {
            scanf("%d %d", &c, &d);
            printf("Result: ");
            int res = GCF(c, d);
            printf("%d\n", res);
        } else {
            dlclose(library);
            return 0;
        }
    }
    return 0;
}