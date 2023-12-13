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
    // argument contains only digit characters
    int check = 0;
    if (argc == 2)
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                check = 0;
                printf("Usage: ./caesar key\n");
                return 1;

            }
            else
            {
                check = 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //converting argument to an integer
    int key = atoi(argv[1]);
    // getting the plaintext
    string plain = get_string("plaintext: ");
    //encipher
    string cipher = plain;
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isalpha(plain[i]))
        {
            cipher[i] = (int) plain[i] + key;
            if (isalpha(cipher[i]) == 0)
            {
                for (int m = 0; isalpha(cipher[i]) == 0; m++)
                {
                    cipher[i] = (int) cipher[i] - 26;
                }
            }
        }

    }
    //printing the ciphertext
    printf("ciphertext: %s\n", cipher);
}

