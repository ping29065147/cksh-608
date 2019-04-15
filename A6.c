#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, a;

    for(i=0; i<5; i++){
        for(a=i; a>0; a--)
            printf(" ");
        for(a=3; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
