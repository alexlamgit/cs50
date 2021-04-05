#include <stdio.h>
#include <cs50.h>
#include <math.h>

//The reason why I ask the user to input for a second time is because
//I modified the input by dividing by ten, but need an unalterde version of
//the credit card number later in my code. Instead of rewriting all of my
//variables, I decided to create a new one called card2


//bool checksum(long card, )

int main(void)
{

    long total;
    long length;
    long card;
    long card2;
    long card3;
    long l;

    do
    {
    card2 = get_long("Card number:\n");
    card = card2/10;
    card3 = card2;
    l = card;
    

    total = 0;
    length = 0;
    while (l>1)
    {
        l /= 10;
        length++;
    }
    int a;
    if (length%2==0)
    {
        a = length/2;
    }
    else
    {
        a = (length+1)/2;
    }

    long every_other[a];
    long every_other_other[a];
    
    for (int i = 0; i < a; i++)
    {
        every_other[i] = 2*(card%10);
        card = card/100;
        total += (every_other[i])/10 + (every_other[i])%10;

        every_other_other[i] = (card2%10);
        card2 = card2/100;
        total += (every_other_other[i])/10 + (every_other_other[i])%10;
    }
    
    } while (total != 20);

    

    if ((card3 >= 34e13 && card3 < 35e13) || (card3 >= 37e13 && card3 < 38e13))
    {
        printf("AMEX\n");
    }
    else if ((card3 >= 51e14 && card3 < 51e14) || (card3 >= 52e14 && card3 < 53e14) || (card3 >= 53e14 && card3 < 54e14) || (card3 >= 54e14 && card3 < 55e14) || (card3 >= 55e14 && card3 < 56e14))
    {
        printf("MASTERCARD\n");
    }
    else if ((card3 >= 4e12 && card3 < 5e12) || (card3 >= 4e15 && card3 < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}