#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define Q 25
#define D 10
#define N 5
#define P 1 


int main(void)
{
    float change;
    do 
    {
        change = get_float("Change owned: ");
    }
    while (change < 0);
    
    int cents = round(change * 100);
    int owned = 0;

    int numquarts = cents / Q;
    cents -= numquarts * Q;
    owned += numquarts;

    int numdimes = cents / D;
    cents -= numdimes * D;
    owned += numdimes;

    int numnickels = cents / N;
    cents -= numnickels * N;
    owned += numnickels;
    
    int numpennies = cents / P;
    cents -= numpennies * P;
    owned += numpennies;
    
    printf("%i\n", owned);
}





