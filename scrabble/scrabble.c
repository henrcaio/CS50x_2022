#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void result(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Send scores to result function
    result(score1, score2);
}

int compute_score(string word)
{
    int sum = 0, letter = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)    // Goes through every character
    {
        if (toupper(word[i]) >= 65 && toupper(word[i]) <= 90) // Checks if character is a letter
        {
            letter = (toupper(word[i]) - 65);
            sum += POINTS[letter];
        }
    }
    return sum;
}

// Checks winner
void result(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}