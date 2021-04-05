#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Function to count the letters in the inputted text. Pretty self explanatory.
int numletters(string t)
{
    int letters = 0;
    for (int i = 0; i < strlen(t); i++)
    {
        if (isalpha(t[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}

//Function to check the number of words in the inputted text.
int numwords(string t)
{
    int words = 0;
    int space_encountered = 1;
    for (int i = 0; i < strlen(t); i++)
    {
        if (t[i] != ' ' && space_encountered == 1)
        {
            if (isalpha(t[i]) != 0)
            {
                words++;

                //After the check for a character, the program
                //will skip all other characters in the word
                //until it reaches a space, indicating the start of a new word.

                space_encountered = 0;
            }
        }
        else if (t[i] == ' ')
        {
            space_encountered = 1;
        }
    }
    return words;
}

//Function to check the number of sentences. Similar to the word check except the condition is different.
int numsentences(string t)
{
    int sentences = 0;
    int punctuation_encountered = 1;

    for (int i = 0; i < strlen(t); i++)
    {
        bool punc_check = t[i] != '!' || t[i] != '.' || t[i] != '?';
        if (punc_check && punctuation_encountered == 1)
        {
            if (isalpha(t[i]) != 0)
            {
                sentences++;
                /*
                After the check for a character, the program
                will skip all other words of the sentence until
                it reaches a punctuation mark, indicating the start of a new sentence.
                */
                punctuation_encountered = 0;
            }
        }
        else if (t[i] == '!' || t[i] == '.' || t[i] == '?')
        {
            punctuation_encountered = 1;
        }
    }
    return sentences;
}

//Main function where the Coleman-Liau index will be calculated.
int main(void)
{
    string text = get_string("Text: ");

    float words = (float) numwords(text);
    float letters_per100 = (numletters(text) * 100) / words;
    float sentences_per100 = (numsentences(text) * 100) / words;
    int index = round(0.0588 * letters_per100 - 0.296 * sentences_per100 - 15.8);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    //I apparently need to add more comments but
    //any more comments that that and this program will
    //become an essay lol... what fucking function are
    //they using to check this shit? My code documented
    //like a national geographic documentary and its still
    //not engough shiii...
}