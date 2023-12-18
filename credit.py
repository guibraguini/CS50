from cs50 import get_int
import math

cardNumber = get_int("what's the credit card number?")
digitCount = 0
firstsDigits = 0
sumTotal = 0
# repeat while there's non processed numbers on card number's
while (cardNumber != 0):
    if (cardNumber < 100 and cardNumber >= 10):

        firstsDigits = cardNumber

    digit = cardNumber % 10
    cardNumber = cardNumber / 10
    # use math.trunc to truncate the value
    cardNumber = math.trunc(cardNumber)
    # use the counter of digits to check if its other
    if (digitCount % 2 == 0):

        sumTotal += digit

    else:

        # check if digit * 2 has more than 1 digit
        if (digit * 2 < 10):
            sumTotal += (digit * 2)
        else:
            # if digit has more than 1 digit pick up the 2 digits separately and adds them to the sun using math.trunc to truncate the values
            sumTotal += ((digit * 2) % 10) + math.trunc(((digit * 2) / 10))
    digitCount += 1
# check if Luhn’s Algorithm work's
if (sumTotal % 10 == 0):
    # check if the card belong's to AMEX, MASTERCARD, VISA or does not belong to any at all
    if (digitCount == 15 and (firstsDigits == 34 or firstsDigits == 37)):
        print("AMEX")
    elif(digitCount == 16 and (firstsDigits >= 51 and firstsDigits <= 55)):
        print("MASTERCARD")
    elif ((digitCount == 13 or digitCount == 16) and (firstsDigits >= 40 and firstsDigits <= 49)):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
