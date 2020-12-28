#include <cs50.h>
#include <ctype.h>
#include <stdio.h>


int main(void)
{
    char *s = get_string("s: ");

    // char *t = s;

    char *t = malloc(strlen(s) + 1);

    strcpy(t, s);

    t[0] = toupper(t[0]);

    printf("%s\n", s);
    printf("%s\n", t);
}

/*void  add_one_by_reference(int *num);
void  add_one_by_value(int num);

int main(void)
{
    int num = 1;

    add_one_by_reference(&num);
    add_one_by_value(num);

    printf("%i \n", num);

    return 0;
}

void add_one_by_reference(int *num)
{
    *num = *num + 1;
}

void  add_one_by_value(int num)
{
    num = num + 1;
}*/