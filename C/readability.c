#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int calc_readabil(string text);

int main(void)
{
    //Get text from user and calculate the Coleman-Liau index
    string text = get_string("Text: ");
    int grade_level = calc_readabil(text);

    // Check to see if Coleman-Liau index is less than 1 or greater than 16, and print the index
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}

int calc_readabil(string text)
{
    // Count the number of letters, words, and sentences in the text
    int letters = 0, words = 0, sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int num = (int) toupper(text[i]);
        if (num >= 65 && num <= 90)
        {
            letters++;
        }
        else if (num == 32)
        {
            words++;
        }
        else if (num == 46 || num == 33 || num == 63)
        {
            sentences++;
            if (i == n - 1)
            {
                words++;
            }
        }
    }
    // Calculate the Coleman-Liau index
    float cl_float = 0.0588 * ((float) letters / (float) words * 100.0) - 0.296 * ((float) sentences / (float) words * 100.0) - 15.8;
    int cl_int = (int) round(cl_float);

    return cl_int;
}
