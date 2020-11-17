#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, a;

    for(i=5; i>0; i--){
        for(a=2; a>0; a--)
            printf(" ");
        for(a=4; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
