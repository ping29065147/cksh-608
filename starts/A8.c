#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, a, b;

    for(i=5, j=4; i>0; i--, j--){
        for(b=j; b>0; b--)
            printf(" ");
        for(a=i; a>0; a--)
            printf("*");
        printf("\n");
    }

    return 0;
}
