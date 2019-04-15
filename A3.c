#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, a, b;

    for(i=1, j=4; i<6; i++, j--){
        for(b=j; b>0; b--)
            printf(" ");
        for(a=i; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
