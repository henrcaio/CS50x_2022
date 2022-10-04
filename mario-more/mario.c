#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
    int height;

    do
    {
        height = get_int("How tall is your pyramid? "); //gets input from user
    }
    while (height < 1 || height > 8);

    pyramid(height);
}



void pyramid(int height)
{
    for (int i = 0; i < height; i++) //lines
    {
        for (int k = (height - i); k > 1; k--) //spaces before bricks
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++) //horizontal bricks left side
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++) //horizontal bricks right side
        {
            printf("#");
        }
        printf("\n");
    }
}