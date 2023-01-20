// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (475254);

// Hash table
node *table[N];

// Self declared global variable wordcount
unsigned int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index;
    if (word[1] == '\0')
    {
        index = ((int) tolower(word[0]) - 97) * 18278;
        return index;
    }
    else if (word[2] == '\0')
    {
        index = ((int) tolower(word[0]) - 97) * 18278 + ((int) tolower(word[1]) - 97) * 703 + 1;
        return index;
    }
    else if (word[3] == '\0')
    {
        index = (((int) tolower(word[0]) - 97) * 18278) + (((int) tolower(word[1]) - 97) * 703) + ((int) tolower(word[2]) - 97) * 28 + 2;
        return index;
    }
    else
    {
        index = (((int) tolower(word[0]) - 97) * 18278) + (((int) tolower(word[1]) - 97) * 703) + (((int) tolower(word[2]) - 97) * 28) + ((int) tolower(word[3]) - 97) + 3;
        return index;
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    
    // Create the array the dictWord is loaded into
    
    char *dictWord = malloc((sizeof(char)) * (LENGTH + 1));
    
    while (fscanf(f, "%s", dictWord) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
       
        strcpy(n->word, dictWord); // Maybe tolower the actual string -> not necessary; all dictWords are already lowercase
        
        n->next = NULL;
        
        unsigned int index = hash(n->word);
        // See whether table already has an entry. If not, assign the node. If so, first assign the new node.next to the next node, and then the head to the new node.
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            node *tmp = table[index];
            do
            {
                if (tmp->next == NULL)
                {
                    tmp->next = n;
                    break;
                }
                tmp = tmp->next;
            }
            while (tmp != NULL);
        }
        wordCount++;
    }
    fclose(f);
    free(dictWord);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
