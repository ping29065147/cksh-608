#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=2, y=-1;
    int i, j, a, b;

    for(i=1, j=2; i>0; i+=x, j+=y){
        for(b=j; b>0; b--)
            printf(" ");
        for(a=i; a>0; a--)
            printf("*");
        for(b=j; b>0; b--)
            printf(" ");
        printf("\n");
        if (i==5 && j==0){
            x*=-1;
            y*=-1;
        }
    }

    return 0;
}
