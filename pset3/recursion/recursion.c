#include <cs50.h>
#include <stdio.h>

void draw(int h);

int main(void)
{
    int height = get_int("Pyramid size: ");
    draw(height);
}

void draw(h)
{
    if (h == 0)
    {
        return;
    }
    
    draw(h-1);
    
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}