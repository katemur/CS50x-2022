// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"
// counter for words in dictionary
unsigned int wordsInDict = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash the word
    int hash_value = hash(word);
    // access linked list at that index in the hash table
    node *link = table[hash_value];
    // traverse linked list, looking for the word
    while (link != NULL)
    {
        if (strcasecmp(link->word, word) == 0)
        {
            return true;
        }
        link = link->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // define the length of the word
    int len = strlen(word);
    // Hash function from red dragon book
    unsigned int hash = 0;
    for (int i = 0; i < len; i++)
    {
        hash = 65599 * hash + tolower(word[i]);
    }
    return (hash ^ (hash >> 16)) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
    }
    //initialise word array
    char w[LENGTH + 1];
    // Read strings from file one at a time
    while (fscanf(dict, "%s", w) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //copy word into node
        strcpy(n->word, w);
        // Hash word to obtain a hash value
        int hash_value = hash(w);

        //insert node into hash table at that location
        n->next = table[hash_value];
        table[hash_value] = n;
        wordsInDict++;
    }
    //closing dictionary
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (wordsInDict < 0)
    {
        return 0;
    }
    else
    {
        return wordsInDict;
    }

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //iterate through hash table and free nodes in each lonkrd list
    for (int i = 0; i < N; i++)
    {
        //crreating a cursor
        node *cursor = table[i];
        //loop through linked list
        while (cursor != NULL)
        {
            //creating tmp
            node *tmp = cursor;
            //point cursor to next element
            cursor = cursor->next;
            //free tmp
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }

    }
    return false;
}
