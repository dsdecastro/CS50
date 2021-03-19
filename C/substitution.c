// Implement a substitution cypher, with a key provided by the user

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check to confirm there is only one command line argument (aside from "./substitution")
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check to confirm key has a length of 26
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check to confirm key contains each letter of the alphabet only once
    int char_counter[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        int num = (int) toupper(argv[1][i]);
        if (num < 65 || num > 90 || char_counter[num - 65] == 1)
        {
            printf("Key must contain 26 characters, using each letter of the alphabet only once.\n");
            return 1;
        }
        else
        {
            char_counter[num - 65] = 1;
        }
    }

    // Get string from user
    string text = get_string("plaintext:  ");

    // Find length of input text
    int len = strlen(text);

    // Cycle through characters in input text
    for (int i = 0, num = 0; i < len; i++)
    {
        num = (int) text[i];
        // Check if the character is a letter and if it is lowercase,
        // and then add that character to the output string
        if ((num >= 65 && num <= 90) || (num >= 97 && num <= 122))
        {
            if (islower(text[i]))
            {
                text[i] = tolower(argv[1][num - 97]);
            }
            else if (isupper(text[i]))
            {
                text[i] = toupper(argv[1][num - 65]);
            }
        }
    }

    //Print the result
    printf("ciphertext: %s\n", text);

    //Exit the program
    return 0;
}
