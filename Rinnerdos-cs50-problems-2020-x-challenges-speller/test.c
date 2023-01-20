#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


int main(void)
{
    char *word = malloc(sizeof(char)*46);
    
    word = "L";
    unsigned int index;
    
    if (word[1] == '\0')
    {
        unsigned int test = tolower(word[0]);
        char testChar = tolower(word[0]);
        index = ((int) tolower(word[0]) * 703);
        unsigned int test2 = testChar;
        printf("The index is(1): %i\n", index);
        printf("The test value is(1): %i\n", test2);
        printf("The test char is(1): %c\n", testChar);
    }
    else if (word[2] == '\0')
    {
        index = ((int) tolower(word[0]) - 97) * 703 + ((int) tolower(word[1]) - 97) * 28 + 1;
        printf("The index is(2): %i\n", index);
    }
    else
    {
        index = (((int) tolower(word[0]) - 97) * 703) + (((int) tolower(word[2]) - 97) * 28) + ((int) tolower(word[2]) - 97) + 2;
        printf("The index is(3): %i\n", index);
    }
    return 0;
}