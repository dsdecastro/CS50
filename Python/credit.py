from cs50 import get_string
import re


def main():

    # Get the name of the user
    number = get_string("Number: ")

    # Define a list of digits for step 1 of Luhn's Algorithm
    digits = []

    # Multiply the correct digits by two, and add them to the list
    i = len(number) - 2
    while i >= 0:
        digits.append(int(number[i]) * 2)
        i -= 2

    # Sum the digits of the products stored in the digits list
    digit_sum = 0
    for d in digits:
        for i in str(d):
            digit_sum += int(i)

    # Now add the digits that were skipped over before (step 2 of Luhn's Algorithm)
    i = len(number) - 1
    while i >= 0:
        digit_sum += int(number[i])
        i -= 2

    # Check to see if the last digit is zero, and that the number is of correct length
    if (digit_sum % 10 == 0) & (re.match(r"\d{13}|\d{15}|\d{16}", number) != None):
        # Match the number with the correct company
        if re.match(r"(34|37).*", number):
            print("AMEX")
        elif re.match(r"5[1-5].*", number):
            print("MASTERCARD")
        elif re.match(r"4.*", number):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()