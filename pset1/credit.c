#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    //Ask for card number
    long number;
    do
    {
        number = get_long("Number:");
    }
    while (number < 0);
    //Luhn's algorithm
    //checking of the credit card is valid
    int sum = number % 10;
    for (int i = 0; i < 15; i++)
    {
        //determine all the numbers
        long m = pow(10, i + 2);
        long l = pow(10, i + 1);
        int num = (number % m - number % l) / l;
        //multiply every second by 2
        if ((i == 0) || (i == 2) || (i == 4) || (i == 6) || (i == 8) || (i == 10) || (i == 12) || (i == 14))
        {
            if (num > 4)
            {
                num = (num * 2) % 10 + 1;
            }
            else if (num <= 4)
            {
                num = num * 2;
            }
        }
        sum = sum + num;
    }
    //determining the lenght od the number
    int length = 0;
    for (long i = 1; i < number; i *= 10)
    {
        length++;
    }
    // determining first numbers
    long start_number = number;
    for (int i = 0; i < (length - 2); i++)
    {
        start_number = start_number / 10;
    }
    //checking the validity of the card
    if (sum % 10 == 0)
    {
        if ((length == 15) && ((start_number == 34) || (start_number == 37)))
        {
            printf("AMEX\n");
        }
        else if ((length == 16) && (start_number >= 51) && (start_number <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if (((length == 13) || (length == 16)) && ((start_number >= 40) && (start_number < 50)))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}