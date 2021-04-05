#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    do 
    {
        start = get_int("Starting size: ");
    } 
    while (start < 9);

    int end;
    do 
    {
        end = get_int("Ending size: ");
    } 
    while (end < start);

    int years = 0;

    while (start < end)
    {
        int oneyrgain = start/3;
        int oneyrloss = start/4;
        start += oneyrgain - oneyrloss;
        years++;
    }
    printf("Years: %i\n", years);
}
