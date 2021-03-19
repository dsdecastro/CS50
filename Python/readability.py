from cs50 import get_string
import re


def main():

    # Get the name of the user
    text = get_string("Text: ")

    # Move through every character in the text, adding 1 to the counters for letters, words, and sentences when appropriate
    letters = 0
    words = 0
    sentences = 0
    for c in text:
        if re.match(r"[A-Z]", c.upper()):
            letters += 1
        elif re.match(r" ", c):
            words += 1
        elif re.match(r"[\!\?\.]", c):
            sentences += 1

    # Check to see if text ends in a space; if not, increase the number of words by 1
    if re.match(r" ", text[len(text) - 1]) == None:
        words += 1

    # Calculate the index
    index = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8

    # Check to see if the index < 1 or index >= 16, and print appropriate response
    if index <= 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        # Add 0.5 to index to ensure computer will round correctly
        print(f"Grade {int(index + 0.5)}")


if __name__ == "__main__":
    main()