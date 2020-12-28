#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string validate_key(string key);

int main(int argc, string argv[])
{
    string key = "";
    string plain_text;
    string validation_error;

    // Get key from the command line
    if (argc == 2)
    {
        key = argv[1];
    }

    // validate key
    validation_error = validate_key(key);

    if (validation_error != 0)
    {
        printf("%s\n", validation_error);
        return 1;
    }

    // Get plaintext
    plain_text = get_string("plaintext: ");

    // Encipher
    string english_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int plain_text_length = strlen(plain_text);
    char ciphertext[1000] = "";

    // loop through plain text
    for (int i = 0; i <= strlen(plain_text); i++)
    {
        // map char index in english_alphabet
        char *pointer = strchr(english_alphabet, toupper(plain_text[i]));
        if (pointer)
        {
            int index = (int)(pointer - english_alphabet);
            // find respective letter in the entered key and standardize it to uppercase
            char mapped_key = toupper(key[index]);

            if (islower(plain_text[i]))
            {
                // set letter to lower case if that's the case
                mapped_key = tolower(mapped_key);
            }

            strncat(ciphertext, &mapped_key, 1);
        }
        else
        {
            strncat(ciphertext, &plain_text[i], 1);
        }
    }

    // Print ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string validate_key(string key)
{
    int key_length = strlen(key);

    // EX: $ ./substitution
    // Usage: ./substitution key
    if (!key || key_length == 0)
    {
        return "Usage: ./substitution key";
    }

    if (key_length < 26 || key_length > 26)
    {
        // EX: $ ./substitution ABC
        // Key must contain 26 characters.
        return "Key must contain 26 characters.";
    }

    char memoize_characters[26];

    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            // $ ./substitution VCHPRZGJNTLSKFBDQWAXEUYM56
            // Key must only contain alphabetic numbers
            return "Key must only contain alphabetic numbers.";
        }

        memoize_characters[i] = key[i];

        for (int j = 0; j < i; j++)
        {
            // $ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMVC
            // Key must not contain repeated characters
            if (memoize_characters[j] == key[i])
            {
                return "Key must not contain repeated characters.";
            }
        }
    }

    return 0;
}




