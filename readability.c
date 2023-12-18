#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentenses(string text);

int main(void)
{
    string text = get_string("Text: ");

    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentenses(text);

    //transform letters into a avarage of letters per 100 words
    letters = (100 * letters) / words;

    //transform sentences into a avarage of sentences per 100 words
    sentences = (100 * sentences) / words;


    //calculate the Coleman-Liau index of a text
    float result = 0.0588 * letters - 0.296 * sentences - 15.8;

    //if grade 16+, then print grade 16+ and exit
    if (round(result) >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    //if before grade 1, then print before grade 1 and exit
    else if (round(result) < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    //if not grade 16+ or before grade 1, then print grade and exit
    printf("Grade %.0f\n", round(result));
    return 0;
}

int count_letters(string text)
{
    int count = 0;
    //count how many caracteres the string have
    for (int i = 0; text[i] != '\0'; i++)
    {
        //check if the characateres are alphabetical
        if ((text[i] >= 97 && text[i] <= 122) || (text[i] >= 65 && text[i] <= 90))
        {
            //count every letter
            count++;
        }

    }
    return count;
}
int count_words(string text)
{
    int count = 0;
    //count how many words the string have
    for (int i = 0; text[i] != '\0'; i++)
    {
        //check if its a word
        if (text[i] == ' ')
        {
            //count every time there's a space
            count++;
        }

    }
    return count + 1;
}
int count_sentenses(string text)
{
    int count = 0;
    //count how many sentenses the string have
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] == '?' || text[i] == '!' || text[i] == '.') && ((text[i - 1] >= 97 && text[i - 1] <= 122) || (text[i - 1] >= 65
                && text[i - 1] <= 90)))
        {
            //count every time there's a ?,! or .
            count++;
        }

    }
    return count;
}
