// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table calculate as 2 to the power of 16
const unsigned int N = 65536;

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash word to obtain a hash value
    unsigned int hash_value = hash(word);

    // access linked list at that index in the hash table
    node *cursor = table[hash_value];

    // traverse linked list, looking for the word (strcasecmp)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
// source: https://github.com/stephshea/CS50_Pset5/blob/3d5a85faaa9927d9ba437ff4d5dc098240215ce4/speller/dictionary.c#L33
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //add tolower so it lowers all words in texts so hash values match all dictionary words which are lower
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file");
        return false;
    }

    // read strings from file one at a time
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // copy the value word into the word field of the node we just created
        strcpy((n->word), word);
        n->next = NULL;

        // hash word to obtain a hash value
        unsigned int index = hash(word);

        // insert node into hash table at that location
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // loop through array of linked lists
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // traverse linked list
        while (cursor != NULL)
        {
           node *temp = cursor;
           cursor = cursor->next;
           free(temp);
        }
    }

    return true;
}
