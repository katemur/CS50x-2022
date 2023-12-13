#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Ask for wanted change
    float dollars;
    do
    {
        dollars = get_float("Change owed:");
    }
    while (dollars < 0);
    // Converting dollars to cents
    int cents = round(dollars * 100);
    // making a variable for change left
    int change_left = cents;
    // making a variable forr counting coins
    int coins = 0;
    // cheking for quarters
    while (change_left >= 25)
    {
        change_left = change_left - 25;
        coins++;
    }
    // checking for dimes
    while (change_left >= 10)
    {
        change_left = change_left - 10;
        coins++;
    }
    //checking for nickels
    while (change_left >= 5)
    {
        change_left = change_left - 5;
        coins++;
    }
    //checking for pennies
    while (change_left > 0)
    {
        change_left = change_left - 1;
        coins++;
    }
    //printing the result
    printf("%i\n", coins);
}