#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool validate(int arg, string key);
void encipher(string key, string text);

int main(int argc, string argv[])
{
    // Calls function to validate key and, if true, asks for plaintext and calls function to encipher and print it
    if (validate(argc, argv[1]) == true)
    {
        string text = get_string("plaintext:  ");
        encipher(argv[1], text);
    }
    else
    {
        // In case of failure to validate key, exits returning 1
        return 1;
    }
}

// Validates key for length, invalid characters, duplicate characters and too many arguments
bool validate(int arg, string key)
{
    if (arg != 2)    // Checks for too many or no arguments
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    else if (strlen(key) != 26)    // Checks key length
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (!(isalpha(key[i])))   // Checks if all characters are alphabetic
        {
            printf("Key must only contain aphabetic characters\n");
            return false;
        }
        for (int j = 0; j < i; j++)
        {
            if (key[i] == key[j])   // Checks for repeated characters
            {
                printf("Key must not contain repeated characters\n");
                return false;
            }
        }
    }

    // In case all checks were ok, returns true
    return true;
}

// Enciphers text based on key
void encipher(string key, string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) && islower(text[i]))    // If character is alphabetic and lower case
        {
            int ch = text[i] - 97;
            text[i] = tolower(key[ch]);
        }
        else if (isalpha(text[i]) && isupper(text[i]))    // If character is alphabetic and upper case
        {
            int ch = text[i] - 65;
            text[i] = toupper(key[ch]);
        }
        else
        {
            text[i] = text[i];    // If character is not alphabetic, do not encipher
        }
    }

    printf("ciphertext: %s\n", text);    // Prints ciphertext
}