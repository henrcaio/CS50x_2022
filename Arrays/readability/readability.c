#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);
void index(int letters, int words, int sentences);

int main(void)
{
    string input = get_string("Text: "); // Gets input

    int letters = count_letters(input); // Calls function to calculate number of letters
    int words = count_words(input); // Calls function to calculate number of words
    int sentences = count_sentences(input); // Calls function to calculate number of sentences

    index(letters, words, sentences);   // Calls function to calculate and print index
}

// Function to calculate number of letters
int count_letters(string input)
{
    int letters = 0;
    for (int i = 0; i < strlen(input); i++) // Goes through the text
    {
        if (isalpha(input[i])) // If the character is a letter (a to z, case insensitive)
        {
            letters++;
        }
    }

    return letters;
}

// Function to calculate number of words
int count_words(string input)
{
    int words = 0;
    for (int i = 0; i < strlen(input); i++) // Goes through the text
    {
        if (isspace(input[i])) // If the character is a space
        {
            words++;
        }
    }
    words++; //We're calculating words by the space and the last word is not counted in the loop. So we add it here.

    return words;
}

// Function to calculate number of sentences
int count_sentences(string input)
{
    int sentences = 0;
    for (int i = 0; i < strlen(input); i++) // Goes through the text
    {
        if (input[i] == 46 || input[i] == 33 || input[i] == 63) // If the character is a dot, exclamation or question mark
        {
            sentences++;
        }
    }

    return sentences;
}

// Function to calculate index
void index(int letters, int words, int sentences)
{
    int index;
    double result = 0, avg_letters = 0, avg_sentences = 0;

    avg_letters = ((double)letters / words) * 100;  // Calculating average number of letters
    avg_sentences = ((double)sentences / words) * 100;  // Calculating average number of sentences

    result = ((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8); // Calculating index

    index = round(result); // Rounding up the index

    // Checking and printing results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}