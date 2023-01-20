#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool is_letter(char c);
bool is_punctuation(char c);
float count_letters(string text);
float count_words(string text);
float count_sentences(string text);


int main(void)
{
    string text = get_string("Text: ");
  
    float wordcount = 0;
    
    float L = (100 * count_letters(text) / (count_words(text)));
    float S = (100 * count_sentences(text) / (count_words(text)));
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }
    
}

bool is_letter(char c)
{
    if (((((int) c) > 64) && ((int) c) < 91) || ((((int) c) > 96) && ((int) c) < 123) || (int) c == 45 || (int) c == 39)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_punctuation(char c)
{
    if ((int) c == 33 || (int) c == 46 || (int) c == 63)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float count_letters(string text)
{
    float lettercount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_letter(text[i]))
        {
            lettercount++;
        }
        if (((int) text[i] == 45 || (int) text[i] == 39))
        {
            lettercount--;
        }
    }
    return lettercount;
}

float count_words(string text)
{
    float wordcount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_letter(text[i]) && !is_letter(text[i + 1]))
        {
            wordcount++;
        }
    }
    return wordcount;
}

float count_sentences(string text)
{
    float sentencecount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_letter(text[i]) && (is_punctuation(text[i + 1])))
        {
            sentencecount++;
        }
    }
    return sentencecount;
}