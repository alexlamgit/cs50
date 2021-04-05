#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int width = get_int("How wide do you want your pyramid to be?\n");
    int left_to1 = width;
    //int left_to2 = width;
    
    for (int i=0; i<width; i++){
        for (int j=0; j<left_to1-1; j++){
            printf(".");
        }
    for (int k=0; k<width; k++){
          for (int l=0; l<left_to1-(left_to1-1); l++){
              printf("#");
          }
            }
        printf("\n");
        left_to1--;
    }

}