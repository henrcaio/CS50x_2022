#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents = 0;
    do
    {
        cents = get_int("How many cents do you owe? ");
    }
    while (cents < 1);  //checks the input for negative numbers
    return cents;
}

int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25) //while cents is bigger than 25, subtract 25 from cents and one coin is added and returned to main
    {
        quarters++;
        cents -= 25;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;
    while (cents >= 10) //while cents is bigger than 10, subtract 10 from cents and one coin is added and returned to main
    {
        dimes++;
        cents -= 10;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;
    while (cents >= 5)  //while cents is bigger than 5, subtract 5 from cents and one coin is added and returned to main
    {
        nickels++;
        cents -= 5;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;
    while (cents >= 1)  //while cents is bigger than 1, subtract 1 from cents and one coin is added and returned to main
    {
        pennies++;
        cents -= 1;
    }
    return pennies;
}
