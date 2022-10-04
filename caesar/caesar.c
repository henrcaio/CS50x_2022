#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string str);
char rotate(int key, char letter);

int main(int argc, string argv[])
{
    // Checking arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //  Calls function and checks if argument is a digit
    if (only_digits(argv[1]) == true)
    {
        int key = atoi(argv[1]);
        string text = get_string("plaintext:  ");
        printf("\nciphertext: ");

        //  Goes through plaintext and calls function rotate to encipher each letter then prints it
        for (int i = 0; i < strlen(text); i++)
        {
            int letter = text[i];
            printf("%c", rotate(key, letter));
        }
        printf("\n");
    }
    //  If argument is not a digit, exits with 1;
    else
    {
        return 1;
    }
}

//  Checks if argument is a digit
bool only_digits(string str)
{
    //  Goes through argument and checks if it is a number
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Turns plaintext in ciphertext
char rotate(int key, char letter)
{
    while (key > 26)
    {
        key -= 26;
    }

    // Checks if character is a letter
    if (toupper(letter) >= 'A' && toupper(letter) <= 'Z')
    {
        letter = letter + key;
        if (toupper(letter) > 'Z')  // Wraps around from Z to A
        {
            letter -= 26;
        }
    }

    return letter;
}