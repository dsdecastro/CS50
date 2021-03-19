// Print a pyramid in the style of the Super Mario

#include <stdio.h>
#include <cs50.h>

int get_height(void);
void print_pyramid(int height);
void print_row(int row, int height);

int main(void)
{
    //Get height input from user
    int height = get_height();

    //Print pyramid
    print_pyramid(height);
}

int get_height(void)
{
    //Get the height from the user
    int height = get_int("Height: ");
    bool height_ok = false;

    //Ensure the height satisfies the given conditions
    do
    {
        if (height < 1 || height > 8)
        {
            height = get_int("Height: ");
        }
        else
        {
            height_ok = true;
        }
    }
    while (!height_ok);

    return height;
}

void print_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        print_row(i, height);
    }
}

void print_row(int row, int height)
{
    //Find the number of spaces needed for the row
    int number_spaces = height - row;

    //Print spaces before hashes
    for (int i = 0; i < number_spaces - 1; i++)
    {
        printf(" ");
    }

    //Add hashes to each row
    for (int i = 0; i <= row; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i <= row; i++)
    {
        printf("#");
    }

    printf("\n");
}
