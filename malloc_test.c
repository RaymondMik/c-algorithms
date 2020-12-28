#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// goal: dynamically change length of list by reallocating its memory
int main(void)
{
    const int short_list_length = 3;
    const int long_list_length = 4;

    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    for (int i = 0; i < short_list_length; i++)
    {
        list[i] = i + 1;
    }

    printf("%i %i %i\n", list[0], list[1], list[2]);

    // we need a tmp var in order to not loose the pointer to the chunk of memory used for list
    int *tmp = realloc(list, long_list_length * sizeof(int));
    if (tmp == NULL)
    {
        return 1;
    }

    tmp[3] = 4;

    list = tmp;

    printf("%i %i %i %i\n", list[0], list[1], list[2], list[3]);

    free(list);
}