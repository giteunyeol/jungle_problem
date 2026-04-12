#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {

        for (int j = 2; j > i; j--)
        {
            printf(" ");
        }
        printf("*");
        for (int k = i; k > 0; k--)
        {
            printf("**");
        }
        printf("\n");
    }
    
    
    
    return 0;
}