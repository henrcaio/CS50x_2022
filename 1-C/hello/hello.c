#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? "); //gets a name as an input
    printf("hello, %s! \nWelcome to CS50.\n", name); //prints the name provided by the user
}