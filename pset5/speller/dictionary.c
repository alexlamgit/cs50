// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 99999;

// Number of words in dictionary
int numw = 0;

// Loaded indicator
bool loaded = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    {
        for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
        {
            if ((strcasecmp(word, tmp->word)) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

/*
    Hashes word to an index
    All credits go to Dan Bernstein (djb2)
*/
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *wordcpy = malloc(LENGTH + 1);
    if (wordcpy == NULL)
    {
        printf("Not enough memory. ");
        return false;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Not enough memory. ");
        return false;
    }

    while (fscanf(dict, "%s", wordcpy) != EOF)
    {
        numw++;
        
        // Node for the word in dictionary
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory. ");
            return false;
        }

        // Fill the "word" field of node
        strcpy(n->word, wordcpy);

        // Get index in which to put the node
        int index = hash(wordcpy);

        n->next = table[index];
        table[index] = n;
    }

    fclose(dict);
    free(wordcpy);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return loaded ? numw : 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
