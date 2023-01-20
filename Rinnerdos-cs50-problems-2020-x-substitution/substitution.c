#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool is_upper(char c);
bool is_lower(char c);

int main(int argc, string argv[])
{
    //First provide the various error messages if the input is wrong.
    if (argc == 1)
    {
        printf("Provide key.\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Provide only the key.\n");
        return 1;
    }
    
    if (strlen(argv[1]) != 26)
    {
        printf("Provide key of correct length.\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!is_upper(argv[1][i]) && !is_lower(argv[1][i]))
        {
            printf("Provide correct key1.\n");
            return 1;
        }
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if ((int) argv[1][i] == (int) argv[1][j])
            {
                printf("Provide correct key2.\n");
                return 1;
            }
        }
    }
    
    // Ask user for the message to be encrypted.
    printf("plaintext: ");
    string plaintext = get_string("");
    
    int diff_upp[26];
    int diff_low[26];
    int ascii_low[26];
    int ascii_upp[26];
    int cypher_low[26];
    int cypher_upp[26];
    string alphabet_low = "abcdefghijklmnopqrstuvwxyz";
    string alphabet_upp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // First get arrays of the alphabet ASCII for upper and lowercase.
    for (int i = 0; i < strlen(alphabet_low); i++)
    {
        ascii_low[i] = (int) alphabet_low[i];
        ascii_upp[i] = (int) alphabet_upp[i];
    }
    
    //Then get the key converted to ASCII and calculate the difference between the alphabet ASCII and the key ASCII. This difference must be applied to the plaintext to obtain the cyphertext.
    //Doing this for both upper and lowercases will prove useful I think, because you can check later if the plaintext char is upper or lower, and then use the correct differnece.
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        cypher_upp[i] = (int) toupper(argv[1][i]);
        cypher_low[i] = (int) tolower(argv[1][i]);
        diff_upp[i] = ascii_upp[i] - cypher_upp[i];
        diff_low[i] = ascii_upp[i] - cypher_upp[i];
    }
    
    // Now apply the difference, and cast it back to a string (cyphertext)
    int plain_ascii[strlen(plaintext)];
    int cypher_ascii[strlen(plaintext)];
    char cyphertext[strlen(plaintext)];
    cyphertext[strlen(plaintext)] = '\0';
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (is_upper(plaintext[i]))
        {
            plain_ascii[i] = (int) plaintext[i];
            cypher_ascii[i] = plaintext[i] - diff_upp[(int) plaintext[i] - 65];
            cyphertext[i] = (char) cypher_ascii[i];
        }
        else if (is_lower(plaintext[i]))
        {
            plain_ascii[i] = (int) plaintext[i];
            cypher_ascii[i] = plaintext[i] - diff_low[(int) plaintext[i] - 97];
            cyphertext[i] = (char) cypher_ascii[i];
        }
        else
        {
            cyphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", cyphertext);
    return 0;
}

bool is_upper(char c)
{
    if ((((int) c) > 64) && ((int) c) < 91)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_lower(char c)
{
    if ((((int) c) > 96) && ((int) c) < 123)
    {
        return true;
    }
    else
    {
        return false;
    }
}