#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j, b;

    for(j=4; j>-1; j--){
        for(b=j; b>0; b--)
            printf(" ");
        printf("*");
        printf("\n");
    }

    return 0;
}
