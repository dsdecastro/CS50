#include <stdio.h>
#include <cs50.h>
#include <math.h>

string validate_number(void);
string get_company(int *num_array);

int main(void)
{
    string result = validate_number();
    printf("%s\n", result);
}

string validate_number(void)
{
    //Get number from user
    long num = get_long("Number: ");

    //Find how many digits the number has
    int length;
    if (num / pow(10, 13) < 1)
    {
        length = 13;
    }
    else if (num / pow(10, 15) < 1)
    {
        length = 15;
    }
    else if (num / pow(10, 16) < 1)
    {
        length = 16;
    }
    else
    {
        printf("failed here\n");
        return "INVALID";
    }

    //Convert the number to an array
    int num_array[length];
    for (int i = 0; i < length; i++)
    {
        num_array[length - 1 - i] = num % 10;
        num = num / 10;
    }

    //Take every other digit and multiply by two
    int every_other_len = length / 2;
    int every_other[every_other_len];
    int j = every_other_len - 1;
    for (int i = length - 2; i >= 0; i -= 2)
    {
        every_other[j] = num_array[i] * 2;
        j--;
    }

    //Sum the digits from the resulting integers
    int sum = 0;
    char two_digits[2];
    for (int i = 0; i < every_other_len; i++)
    {
        if (every_other[i] < 10)
        {
            sum += every_other[i];
        }
        else
        {
            two_digits[1] = every_other[i] % 10;
            two_digits[0] = every_other[i] / 10;
            sum += two_digits[0];
            sum += two_digits[1];
        }
    }

    //Add this sum to the sum of the remaining digits from the original credit card number
    for (int i = length - 1; i >= 0; i -= 2)
    {
        sum += num_array[i];
    }

    // Check if number is valid, and print out credit card type
    if (sum % 10 == 0)
    {
        return get_company(num_array);
    }
    else
    {
        return "INVALID";
    }
}

string get_company(int *num_array)
{
    //Identify the credit card company based on the first two digits of the credit card number
    if (num_array[0] == 4)
    {
        return "VISA";
    }
    else if (num_array[0] == 3 && (num_array[1] == 4 || num_array[1] == 7))
    {
        return "AMEX";
    }
    else if (num_array[0] == 5 && (num_array[1] == 1 || num_array[1] == 2 || num_array[1] == 3 || num_array[1] == 4
                                   || num_array[1] == 5))
    {
        return "MASTERCARD";
    }
    else
    {
        return "INVALID";
    }
}