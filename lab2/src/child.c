#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    float res;
    res = 0;
    float x;
    while (scanf("%f",&x)!=EOF){
        res+=x;
    }
    write(1,&res,sizeof(float));
}