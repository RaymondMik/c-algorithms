#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for their name
    string user_name = get_string("What's your name? ");
    // Print name
    printf("hello, %s \n", user_name);
}
