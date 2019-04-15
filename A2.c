#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=1, a;

    for(; i<6; i++){
        for(a=i; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
