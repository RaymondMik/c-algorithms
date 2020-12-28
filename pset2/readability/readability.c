#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int findColemanLiauIndex(int letters, int words, int sentences);

int main(void)
{
    string user_input;
    int num_of_letters = 0;
    int num_of_words = 0;
    int num_of_sentences = 0;
    int index;

    do
    {
        user_input = get_string("Text: ");
    }
    while (!user_input);

    for (int i = 0; i < strlen(user_input); i++)
    {
        // loop through the text and use ctype to count only letters
        if (isalpha(user_input[i]))
        {
            num_of_letters++;
        }

        // words are separated by spaces (e.g. "hello," is a word)
        if (user_input[i] == ' ')
        {
            num_of_words++;
        }

        // sentences are separated by . ? !
        if (user_input[i] == '.' || user_input[i] == '?' || user_input[i] == '!')
        {
            num_of_sentences++;
        }
    }

    // the total number of words is equal to numbers of empty spaces + 1;
    if (num_of_words > 0)
    {
        num_of_words++;
    }

    index = findColemanLiauIndex(num_of_letters, num_of_words, num_of_sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %i\n", index);
}

int findColemanLiauIndex(int num_of_letters, int num_of_words, int num_of_sentences)
{
    // L is the average number of letters per 100 words in the text
    float L = ((float) num_of_letters / (float) num_of_words) * 100.00;

    // S is the average number of sentences per 100 words in the text
    float S = ((float) num_of_sentences / (float) num_of_words) * 100.00;

    // Coleman Liau index = 0.0588 * L - 0.296 * S - 15.8;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    return round(index);
}
