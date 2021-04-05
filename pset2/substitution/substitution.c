#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string alphabet_lower = "abcdefghijklmnopqrstuvwxyz";
string alphabet_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//pt = plain text & ck = cipher key. Abreviated for simplicity's sake.
string cipher(string pt, string ck)
{    
    char ck_lower[26];
    char ck_upper[26];
    //Had to manually assign the memory for the ciphered string otherwise
    //it would not work...
    char *ciphered = calloc(96, sizeof(char *));
    
    //Creates a string that stores the values of the key in lowercase 
    // and in uppercase.
    for (int u = 0; u < strlen(ck); u++)
    {
        ck_lower[u] = tolower(ck[u]);
        ck_upper[u] = toupper(ck[u]);
    }

    //For each character in the plaintext string, 
    for (int i = 0; i < strlen(pt); i++)
    {
        //Check wether that character is a letter, 
        for (int j = 0; j < 26; j++)
        {
            if (isalpha(pt[i]) != 0)
            {
                //If it is a letter, check wether it's lowercase or upper.
                //Then assign the corresponding value to the ciphered string.
                if (pt[i] == alphabet_lower[j])
                {
                    ciphered[i] = ck_lower[j];
                }
                else if (pt[i] == alphabet_upper[j])
                {
                    ciphered[i] = ck_upper[j];   
                }
            }
            //If the current character is not in the alphabet just ignore it. 
            else if (pt[i] != alphabet_lower[j] || pt[i] != alphabet_upper[j])
            {
                ciphered[i] = pt[i];
            }
        }
    }
    return ciphered;
}

//function to check for duplicates
int check_dupe(string key)
{
    for (int t = 0; t < strlen(key); t++)
    {
        for (int q = t + 1; q < strlen(key); q++)
        {
            if (key[t] == key[q])
            {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, string argv[])
{
    //If user inputs less than, or more than 1 arguments,
    //the program will return 1 indicating an error.
    if (argc != 2)
    {
        printf("Error: Command line argument not correctly provided.\n");
        return 1;
    }
    for (int k = 0; k < strlen(argv[1]) - 1; k++)
    {
        if (isalpha(argv[1][k]) == 0 || strlen(argv[1]) != 26 || check_dupe(argv[1]) == 1)
        {
            printf("Error: Invalid key.\n");
            return 1;
        }
    }
    
    string plaintext = get_string("plaintext: "); 
    printf("ciphertext: %s\n", cipher(plaintext, argv[1]));
    return 0;
}