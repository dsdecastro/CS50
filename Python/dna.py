import sys
import re
from copy import copy
from csv import DictReader


def main():

    # Check for the correct number of command line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.csv")
        sys.exit(1)

    # Read database into memory
    people = []
    with open(sys.argv[1], "r") as file:
        reader = DictReader(file)
        for row in reader:
            people.append(row)

    # Read sequence into memory
    sequence = ""
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Calculate the number of repetitions of each STR, and store in a new dictionary
    unknown = {}
    for key in people[0].keys():
        if key != "name":
            unknown[key] = str(count_STR(sequence, key))

    # Compare each dictionary in the list people with the dictionary of the unknown person
    match = False
    for person in people:
        # Make a copy of person to avoid changing the original
        p = copy(person)
        p.pop("name")
        if p == unknown:
            match = True
            print(person["name"])

    # If there was no match in the people list
    if not match:
        print("No match")

    sys.exit(0)


def count_STR(sequence, STR):
    # Identify a given STR in a DNA sequence, and count the number of time it repeats
    matches = re.finditer(rf"({STR})+", sequence)

    match_list = [m for m in matches]

    if len(match_list) < 1:
        return 0

    # Sort the list of matches if the length is greater than 1
    if len(match_list) > 1:
        # If so, perform a selection sort (descending) based on the number of repetitions of the STR in each match
        i = 0
        while i < len(match_list) - 1:
            high = i
            j = i + 1

            while j < len(match_list):
                if repetitions(match_list[high], STR) < repetitions(match_list[j], STR):
                    high = j
                j += 1

            if high != i:
                temp = match_list[i]
                match_list[i] = match_list[high]
                match_list[high] = temp

            i += 1

    # Return the highest number of repetitions
    return repetitions(match_list[0], STR)


def repetitions(match, STR):
    # Return the number of repititions of a STR given a re.match object
    return int((match.end() - match.start()) / len(STR))


if __name__ == "__main__":
    main()