#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int w;
    
    //Do while loop for the user input
    do
    {
        w = get_int("How wide?\n");
    }
    while (w < 1 || w > 8);

    //First for loop is the main; it repeats w times and the i value increments by 1
    for (int i = 0; i < w; i++)
    {
        //The second for loop prints the spaces. It starts of with a j value of 7 and is decremented by one until it is no longer greater than i. 
        for (int j = w - 1; j > i; j--)
        {
            printf(" ");
        }
        //The third for loop prints the #. It continues as long as k is less than i+1. 
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        printf("  ");
        
        //Final loop which constructs the second pyramid. Refers to the row position to see how many # to print. 
        for (int m = 0; m <= i; m++)
        {
            printf("#");
        }
        
        printf("\n");
    }
    
}
