#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Ask for wanted height
    int height;
    do 
    {
        height = get_int("Height:");
    }
    while ((height > 8) || (height < 1));
    
    for (int i = 0; i < height; i++)
    {
        //printing spaces
        for (int p = height - 1; p > i; p--)
        {
            printf(" ");
        }
        //printing hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // making space between pyramids
        printf("  ");
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}