#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, a;

    for(i=1; i<6; i++){
        for(a=i; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
