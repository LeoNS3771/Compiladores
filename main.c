#include "stdio.h"

void soma(int a, int b){
    printf("%i", a + b);
}

int main(){
    void (*lambdaSoma) (int, int);
    lambdaSoma = &soma;
    soma(1, 2);
    return 0;
}

