#include <cs50.h>
#include <stdio.h>
#include <math.h>

void checkProcessor(int length, int first, int second);

int main(void)
{

    long number = get_long("Type your Credit Card number: ");
    int number_length = floor(log10(number)) + 1;

    int digit[number_length];
    int sum = 0, multiplied_digit = 0;

    //Adds each number to a specific position of the array "digit".
    for (int i = 0; i < number_length; i++)
    {
        digit[i] = number % 10;
        number = number / 10;
    }

    //Manipulates every other digit starting second-to-last
    for (int i = 0; i < number_length; i++)
    {
        if (i % 2 == 0)
        {
            sum += digit[i];
        }
        else
        {
            multiplied_digit = digit[i] * 2;
            if (multiplied_digit >= 10)   //Adds the product's individual digits if greater than 9
            {
                sum += (multiplied_digit % 10);
                multiplied_digit = multiplied_digit / 10;
                sum += multiplied_digit;
            }
            else    //Adds the product's individual digits if smaller than 10
            {
                sum += multiplied_digit;
            }
        }
    }

    if (sum % 10 == 0)
    {
        checkProcessor(number_length, digit[(number_length - 1)], digit[(number_length - 2)]);
    }
    else
    {
        printf("INVALID\n");
    }
}

//Checks length and first digits then prints answer
void checkProcessor(int length, int first, int second)
{
    if (length == 15)
    {
        if (first == 3 && (second == 4 || second == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 13 || length == 16)
    {
        if (first == 5 && second > 0 && second < 6)
        {
            printf("MASTERCARD\n");
        }
        else if (first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}