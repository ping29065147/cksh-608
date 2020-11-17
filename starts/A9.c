#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=9, j=0, a, b;

    for(; i>0; i-=2, j++){
        for(b=j; b>0; b--)
            printf(" ");
        for(a=i; a>0; a--)
            printf("*");
        for(b=j; b>0; b--)
            printf(" ");
        printf("\n");
    }

    return 0;
}
