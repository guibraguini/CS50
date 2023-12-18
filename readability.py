from cs50 import get_string
import math


def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentenses(text)

    # transform letters into a avarage of letters per 100 words
    letters = (100 * letters) / words

    # transform sentences into a avarage of sentences per 100 words
    sentences = (100 * sentences) / words


    #calculate the Coleman-Liau index of a text
    result = 0.0588 * letters - 0.296 * sentences - 15.8

    # if grade 16+, then print grade 16+ and exit
    if (result >= 16):
        print("Grade 16+\n")

    # if before grade 1, then print before grade 1 and exit
    elif (result < 1):
        print("Before Grade 1")

    #if not grade 16+ or before grade 1, then print grade and exit
    else:
        print("Grade " + str(round(result, 0)))


def count_letters(text):
    count = 0
    count_i = 0
    # count how many caracteres the string have
    for i in text:
        # transform the text into number according to ascii table
        ascii = ord(text[count_i])
        # check if the characateres are alphabetical
        if ((ascii >= 97 and ascii <= 122) or (ascii >= 65 and ascii <= 90)):
            # count every letter
            count += 1
        count_i += 1
    return count

def count_words(text):
    count = 0
    # count how many words the string have
    for i in text:
        # check if its a word
        if (i == ' '):
            #count every time there's a space
            count += 1
    return count + 1

def count_sentenses(text):
    count = 0
    count_i = 0
    # count how many sentenses the string have
    for i in text:
        # transform the text into number according to ascii table
        if (count_i >= 1):
            ascii = ord(text[count_i - 1])

        if ((i == '?' or i == '!' or i == '.') and ((ascii >= 97 and ascii <= 122) or (ascii >= 65
                and ascii <= 90))):
            # count every time there's a ?,! or .
            count += 1
        count_i += 1
    return count

main()
