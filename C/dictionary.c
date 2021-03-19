// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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
const unsigned int N = 26 + 26 * 26 + 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Go to the appropriate bucket
    node *n = table[hash(word)];

    // TODO: fix: make sure case-insensitive
    // Check to see if the word is in the linked list for this bucket
    while (n != NULL)
    {
        if (!strcasecmp(n->word, word))
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) < 2)
    {
        return toupper(word[0]) - 65;
    }
    if (strlen(word) < 3)
    {
        return (toupper(word[0]) - 65) * 26 + (toupper(word[1]) - 65) + 26;
    }
    return (toupper(word[0]) - 65) * 26 * 26 + (toupper(word[1]) - 65) * 26 + (toupper(word[2]) - 65) + 26 * 26 + 26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize table[] to prevent against the use of garbage values
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Define a string to hold the current word
    char *word = malloc(LENGTH + 1);
    int word_index = 0;

    // Define a buffer, then attempt to read the dictionary file
    char *buffer = malloc(1);
    node *new_word;
    while (fread(buffer, 1, 1, dict))
    {
        // Check to see if the current character is not the newline character (dec 10 on the ASCII chart)
        if (*buffer != 10)
        {
            word[word_index] = *buffer;
            word_index++;
        }
        else
        {
            // Terminate the string for the current word
            word[word_index] = '\0';

            // Initialize a new node
            new_word = malloc(sizeof(node));
            if (new_word == NULL)
            {
                return false;
            }
            new_word->next = NULL;

            // Copy current word array to the word of the new node
            for (int i = 0; i < LENGTH; i++)
            {
                new_word->word[i] = word[i];
                if (word[i] == '\0')
                {
                    break;
                }
            }

            // Add the new node to the hash table
            if (table[hash(word)] == NULL)
            {
                table[hash(word)] = new_word;
            }
            else
            {
                new_word->next = table[hash(word)];
                table[hash(word)] = new_word;
            }

            // Prepare for new word
            word_index = 0;
            for (int i = 0; i < LENGTH; i++)
            {
                word[i] = '0';
            }
        }
    }

    // Free memory allocated using malloc
    free(buffer);
    free(word);

    // Close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int words = 0;

    // Loop through the array that is the basis of the hash table
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];

        // Follow the linked list at the current bucket
        while (tmp != NULL)
        {
            words++;
            tmp = tmp->next;
        }
    }

    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through the hash table
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            table[i] = table[i]->next;
            free(tmp);
            tmp = table[i];
        }
    }

    return true;
}
