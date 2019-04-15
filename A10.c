#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, a, b;

    for(i=2, j=8; i<11; i+=2, j-=2){
        for(b=j; b>0; b--)
        printf(" ");
        for(a=i; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
