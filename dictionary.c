// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#include "dictionary.h"

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


// Dictionary
FILE *raw = NULL;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int count = 1;
    //count how many caracters are in the word
    for (int i = 0; word[i]; i++)
    {
        count++;
    }
    // create a variable to recive the lower word
    char lower_word[count];
    //copy the word to the lower_word variable with all the letters being low
    for (int i = 0; word[i]; i++)
    {
        if (isalpha(word[i]) && !isdigit(word[i]))
        {
            lower_word[i] = tolower(word[i]);
        }
        else
        {
            lower_word[i] = word[i];
        }
    }
    // check if there's anything on the position of the table
    if (table[toupper(word[0]) - 'A'] == NULL)
    {
        return false;
    }
    //creates a variable to go from node through node and give it the initial point
    node *d = table[toupper(word[0]) - 'A'];
    //go from node to node checking if it found the word or if there's no more nodes
    while (d->next != NULL && strcmp(d->word, lower_word) != 0)
    {
        d = d->next;
    }
    //check if it found the word
    if (strcmp(d->word, lower_word) == 0)
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // create a new pointer to node
    node *new = malloc(sizeof(node));
    // the new variable recives the word value to it word value
    strcpy(new->word, word);;
    //check if there's something on that spot of the table
    if (table[toupper(word[0]) - 'A'] == NULL)
    {
        //if it dosen't then populate it and return
        table[toupper(word[0]) - 'A'] = new;
        return (toupper(word[0]) - 'A' + 1);
    }
    //if it does then create d and give table as the starting point
    node *d = table[toupper(word[0]) - 'A'];
    int count = 1;
    //go node through node until the next one is empty (NULL) or until find the same word
    while (d->next != NULL && strcmp(d->word, word) != 0)
    {
        d = d->next;
        count++;
    }
    //check if it find the same word and if not then add the new word on the empty spot
    if (d->next == NULL && strcmp(d->word, word) != 0)
    {
        d->next = new;
        count++;
    }
    return (toupper(word[0]) - 'A' + 1) * (10 + count);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open the dictionary
    raw = fopen(dictionary, "r");
    //check if file is opened
    if (raw == NULL)
    {
        return false;
    }
    /**
     * piece of code copied and modified from speller.c
     **/
    int index = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check each word in text
    char c;
    while (fread(&c, sizeof(char), 1, raw))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = tolower(c);
            index++;
        }
        // We must have found a whole word
        else if (!isdigit(c) && index > 0)
        {
            // Terminate current word
            word[index] = '\0';
            index = 0;
            hash(word);
        }
    }
    /**
     * end of copied code
     **/
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //creates a variable to local count
    unsigned int count = 0;
    // loop through all the table array size
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            count++;
            //creates a variable to go from node through node and give it the initial point
            node *d = table[i];
            //go from node to node checking if it found the word or if there's no more nodes
            while (d->next != NULL)
            {
                d = d->next;
                count++;
            }
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loop through all the table array size
    for (int i = 0; i < N; i++)
    {


        if (table[i] != NULL)
        {
            //creates a variable to go from node through node and give it the initial point
            node *d = table[i];
            //go from node to node checking if it found the word or if there's no more nodes
            while (d->next != NULL)
            {
                if (d->next != NULL)
                {
                    d = d->next;
                }
            }
            if (d != NULL)
            {
                free(d);
            }
        }


    }


    // loop through all the table array size checking if everything was unloaded
    if (raw != NULL)
    {
        fclose(raw);
    }

    return true;
}
