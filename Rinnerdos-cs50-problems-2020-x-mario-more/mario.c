#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user for input, repeat if not in correct range (1-8)
    int height;
    do
    {
        height = get_int("Height: \n");
    }
    while (height <= 0 || height > 8); 
    // Now print the pyramid of hashes
    for (int i = 1;  i <= height; i++)
    {
        // First print the empty spaces, opposite of amount of hashes (amount of spaces = height - amount of hashes)
        for (int k = height; k > i; k--)
        {
            printf(" ");
        }

        // Then print the hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // Print the double space in between hashes
        printf("  ");
        // Then print the hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // End each row with a newline
        printf("\n");
    }
}
