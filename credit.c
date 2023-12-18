#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long int cardNumber = get_long("what's the credit card number?");
    int digitCount = 0;
    int firstsDigits = 0;
    int sumTotal = 0;
    //repeat while there's non processed numbers on card number's
    while (cardNumber != 0)
    {
        if (cardNumber < 100 && cardNumber >= 10)
        {
            firstsDigits = cardNumber;
        }
        int digit = cardNumber % 10;
        cardNumber = cardNumber / 10;
        //use the counter of digits to check if its other
        if (digitCount % 2 == 0)
        {
            sumTotal += digit;
        }
        else
        {
            //check if digit * 2 has more than 1 digit
            if (digit * 2 < 10)
            {
                sumTotal += (digit * 2);
            }
            else
            {
                //if digit has more than 1 digit pick up the 2 digits separately and adds them to the sun
                sumTotal += ((digit * 2) % 10) + ((digit * 2) / 10);
            }
        }
        digitCount++;

    }
    //check if Luhn’s Algorithm work's
    if (sumTotal % 10 == 0)
    {
        //check if the card belong's to AMEX, MASTERCARD, VISA or does not belong to any at all
        if (digitCount == 15 && (firstsDigits == 34 || firstsDigits == 37))
        {
            printf("AMEX\n");
        }
        else if (digitCount == 16 && (firstsDigits >= 51 && firstsDigits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((digitCount == 13 || digitCount == 16) && (firstsDigits >= 40 && firstsDigits <= 49))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


    return 0;
}
