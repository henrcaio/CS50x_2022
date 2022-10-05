// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

int total_words = 0;
bool loaded = false;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int key = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (i % 2 == 0)
        {
            key += toupper(word[i]);
        }
        else
        {
            key += (toupper(word[i]) * i);
        }
    }

    key = key % N;

    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Opens and checks file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open file");
        return false;
    }

    //printf("\n\n dictio opened \n");

    char word[LENGTH + 1];

    while (fscanf(dic, "%s", word) != EOF)
    {
        //printf("\n\nfscan ok \n");

        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        //printf("\n ok \n");

        total_words++;

        strcpy(new->word, word);
        new->next = NULL;

        int hash_value = hash(word);


        if (table[hash_value] == NULL)
        {
            table[hash_value] = new;
        }
        else
        {
            new->next = table[hash_value];
            table[hash_value] = new;
        }

        loaded = true;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded == true)
    {
        return total_words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
