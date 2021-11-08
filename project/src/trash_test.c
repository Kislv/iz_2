#include "stdio.h"
#include "stdlib.h"
int main(){
    int a =5;
    printf("%d\n",a);
    int* pa = malloc(sizeof(int)*100);
    *pa =a;
    printf("%d\n",*pa);
    free(pa);
    return 0;
}