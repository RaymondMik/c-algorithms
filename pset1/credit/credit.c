#include <cs50.h>
#include <math.h>
#include <stdio.h>

string validateCardNumber(long long userPrompt);

int main(void)
{
    long long userPrompt;
    // prompt user input
    do
    {
        userPrompt = get_long("Credit card number: ");
    }
    while (!userPrompt);
    printf("%s\n", validateCardNumber(userPrompt));
}

/************************************
    Validate card with checksum
************************************/
string validateCardNumber(long long userPrompt)
{
    long long cardNumberLength = 0;
    long long numberCopy = userPrompt;

    // calculate card number length
    while (numberCopy)
    {
        ++cardNumberLength;
        numberCopy = numberCopy / 10;
    }

    long long divider = 0;
    long long modulo = 0;
    int digit;
    int sumEven = 0;
    int sumOdd = 0;

    // loop through the digits composing the card number, following Luhn’s Algorithm
    for (int i = 1; i <= cardNumberLength; i++)
    {
        if (i == 1)
        {
            // get last digit
            digit = userPrompt % 10;
        }
        else
        {
            // use modulo to get the last nth digits,
            // then divide it by 10, 100, 1000, etc in order to obtain the digit
            // actually corresponding to the position of i in the whole number
            modulo =  pow(10, i);
            divider =  pow(10, i - 1);
            digit = userPrompt % modulo / divider;
        }

        if (i % 2 == 0)
        {
            // do Luhn's algorithm calculations
            int digitTimesTwo = digit * 2;
            if ((digitTimesTwo) > 9)
            {
                sumEven = sumEven + digitTimesTwo % 10;
                sumEven = sumEven + digitTimesTwo / 10 % 10;
            }
            else
            {
                sumEven = sumEven + digitTimesTwo;
            }
        }
        else
        {
            sumOdd = sumOdd + digit;
        }
    }

    int sum = sumEven + sumOdd;
    bool itValidatesLuhnsAlgorithm = sum % 10 == 0;

    // determine card provider
    const int AMEX_LENGTH = 15;
    const int MASTERCARD_LENGTH = 16;
    const int VISA_LENGTH = 13;

    long long firstTwoDigDivider = pow(10, cardNumberLength - 2);
    long long firstDigDivider = pow(10, cardNumberLength - 1);
    int firstTwoDigits = userPrompt / firstTwoDigDivider;
    int firstDigit = userPrompt / firstDigDivider;

    if (itValidatesLuhnsAlgorithm && cardNumberLength == AMEX_LENGTH && (firstTwoDigits == 34 || firstTwoDigits == 37))
    {
        return "AMEX";
    }
    if (itValidatesLuhnsAlgorithm && cardNumberLength == MASTERCARD_LENGTH &&
        (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55))
    {
        return "MASTERCARD";
    }
    if (itValidatesLuhnsAlgorithm && (cardNumberLength == VISA_LENGTH || cardNumberLength == MASTERCARD_LENGTH) && firstDigit == 4)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}
