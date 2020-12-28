#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string hash = "#";
    string emptySpace = " ";
    int gapLength = 2;
    int height;

    // Prompt the user for the pyramid height
    do
    {
        height = get_int("Height: ");
    }
    // define valid height interval
    while (height < 1 || height > 8);
    // loop through the lines
    for (int i = 1; i <= height; i++)
    {
        // loop through the columns
        for (int j = 0; j < height * 2 + gapLength; j++)
        {
            // print left side of the pyramid
            if (j < height)
            {
                if (j < height - i)
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
            }
            // print gap
            if (j > height && j < height + gapLength)
            {
                printf("  ");
            }
            // print right side of the pyramid
            if (j >= height + gapLength && j < height + gapLength + i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
