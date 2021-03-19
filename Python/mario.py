# Print a pyramid alla Super Mario

from cs50 import get_int


def main():
    # Get the height from the user
    while True:
        height = get_int("Height: ")
        if (height >= 1) & (height <= 8):
            break

    # Print out the pyramid
    hashes = 0
    # Cycle through the rows of the pyramid
    while hashes < height:
        # First print out the leading spaces
        i = 0
        while i < (height - hashes - 1):
            print(" ", end="")
            i += 1

        # Then print out the hashes
        i = 0
        while i < hashes:
            print("#", end="")
            i += 1

        # Print out the middle two hashes and the spaces that separate them
        print("#  #", end="")

        # Print out the remaining hashes
        i = 0
        while i < hashes:
            print("#", end="")
            i += 1

        # Print the newline character
        print("")
        hashes += 1


if __name__ == "__main__":
    main()
