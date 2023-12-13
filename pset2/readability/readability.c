#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float count_letters(string txt);
float count_words(string txt);
float count_sentences(string txt);

int main(void)
{
    // Prompting user for a string
    string text = get_string("Text: ");
    //calculating average number of letters per 100 words
    float L = count_letters(text) / count_words(text) * 100.0;
    //calculating average number of sentences per 100 words
    float S = count_sentences(text) / count_words(text) * 100.0;
    //calculating Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // printing the result
    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

}
// A function for counting letters
float count_letters(string txt)
{
    float letters = 0;
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if isupper(txt[i])
        {
            txt[i] = tolower(txt[i]);
        }
        if ((txt[i] >= 'a') && (txt[i] <= 'z'))
        {
            letters++;
        }
    }
    return letters;
}
// A function for counting words
float count_words(string txt)
{
    float words = 1;
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if (txt[i] == ' ')
        {
            words++;
        }
    }
    return words;
}
// A function for counting sentences
float count_sentences(string txt)
{
    float sentences = 0;
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if ((txt[i] == '.') || (txt[i] == '!') || (txt[i] == '?'))
        {
            sentences++;
        }
    }
    return sentences;
}
