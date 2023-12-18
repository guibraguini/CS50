#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int string_lenght(string s);
string substitute(string original, string cipher);
int repetitiveCount(string s);
int checkAlphabet(string s);

int main(int argc, string argv[])
{
    //checks if there's 1 command-line argument
    if (argc != 2)
    {
        printf("error. Please insert 1, and just 1 comand line argument\n");
        //return with error
        return 1;
    }

    //count how many caracteres was on command line
    int count = string_lenght(argv[1]);

    //check if there's 26 characters on command line
    if (count != 26)
    {
        printf("error. The comand line argument must have 26 characters\n");
        //return with error
        return 1;
    }

    if (repetitiveCount(argv[1]) != 0)
    {
        printf("error. Repetitive characters\n");
        //return with error
        return 1;
    }
    if (checkAlphabet(argv[1]) != 0)
    {
        printf("error. The argument dosen't support non alphabetic symbols\n");
        //return with error
        return 1;
    }

    string original = get_string("plaintext: ");
    string ciphered = substitute(original, argv[1]);

    //print the string character by character to prevent error
    printf("ciphertext: ");
    for (int i = 0; i < string_lenght(original); i++)
    {
        printf("%c", ciphered[i]);
    }

    printf("\n");

    return 0;
}

int string_lenght(string s)
{
    int count = 0;

    //count how many caracteres was on command line
    while (s[count] != '\0')
    {
        count++;
    }
    return count;

}

string substitute(string original, string cipher)
{
    //function to substitute the original string for the ciphered one
    int count = 0;

    //original string sized array that will recive all new characters values
    char ciphered[string_lenght(original)];


    //do the substitution
    while (original[count] != '\0')
    {

        //variable that receives the numeric value of the character temporarily
        int tempNum = original[count];
        if ((original[count] >= 97 && original[count] <= 122) || (original[count] >= 65 && original[count] <= 90))
        {

            //check if the character is upcase and change it acordly
            if (isupper(original[count]))
            {
                tempNum -= 97;

                //adds 32 because it's the difference between the uppercase and lowercase character
                tempNum += 32;

                //creates a temp variable for the character
                char tempChar = cipher[tempNum];

                //checks if the character is lowercase or uppercase
                if (isupper(tempChar))
                {
                    tempChar = tolower(tempChar);
                }
                //removes the 32 that was add previously
                ciphered[count] = tempChar - 32;
            }
            else
            {
                tempNum -= 97;
                char tempChar = cipher[tempNum];
                //checks if the character is lowercase or uppercase
                if (isupper(tempChar))
                {
                    tempChar = tolower(tempChar);
                }
                //removes the 32 that was add previously
                ciphered[count] = tempChar;
            }
        }
        else
        {
            ciphered[count] = original[count];
        }
        count++;
    }

    //a string variable that recives all the ciphered values so the function can returns


    string cipheredString = ciphered;

    return cipheredString;
}

int repetitiveCount(string s)
{
    //checks if there's any repeated character one by one making a n*n comparison
    int firstCount = 0;
    while (s[firstCount] != '\0')
    {
        int secondCount = 0;
        while (s[secondCount] != '\0')
        {
            if (firstCount != secondCount && s[firstCount] == s[secondCount])
            {
                return 1;
            }
            secondCount++;
        }
        firstCount++;
    }
    return 0;
}

int checkAlphabet(string s)
{
    //checks if there's any non-alphabetic character one by one making a ascii comparison


    //create a variable to count how many times does each alphabetic character appears
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if ((s[i] >= 97 && s[i] <= 122) || (s[i] >= 65 && s[i] <= 90))
        {
            count++;
        }
    }
    if (count == 26)
    {
        return 0;
    }
    return 1;
}
