#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// getting the key
int main(int argc, string argv[])
{
    //ensure single command-line argument
    string key = argv[1];
    if (argc == 2)
    {
        // cheking key lengh
        if (strlen(key) < 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (strlen(key) == 26)
        {
            // cheking for non-alphabetic characters
            for (int i = 0, n = strlen(key); i < n; i++)
            {
                if (isalpha(key[i]) == 0)
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
            }
            //checking for repeated characters
            for (int i = 0; i < 26; i++)
            {
                for (int j = i + 1; j < 26; j++)
                {
                    if (key[i] == key[j])
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
            }
        }
    }
    else
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    string alphu = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphl = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26; i++)
    {
        if (isupper(key[i]) == 0)
        {
            key[i] = toupper(key[i]);
        }
    }
    // getting the plaintext
    string plain = get_string("plaintext: ");
    string cipher = plain;
    //encipher
    int c = 0; // variable for loops
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isalpha(plain[i]) != 0)
        {
            for (int j = 0; c == 0; j++)
            {
                if (isupper(plain[i]) == 0)
                {
                    if (plain[i] == alphl[j])
                    {
                        cipher[i] = key[j];
                        c = 1;
                    }
                    cipher[i] = tolower(cipher[i]);
                }
                if (islower(plain[i]) == 0)
                {
                    if (plain[i] == alphu[j])
                    {
                        cipher[i] = key[j];
                        c = 1;
                    }
                }
            }
            c = 0;

        }
        else
        {
            cipher[i] = plain[i];
        }
    }


    //printing the ciphertext
    printf("ciphertext: %s\n", cipher);
}