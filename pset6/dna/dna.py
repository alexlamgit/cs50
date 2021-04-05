# Identifies a person based on their DNA

import sys
import csv
from itertools import groupby
import re


def main():

    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCE")

    DATA = []
    with open(sys.argv[1], 'r') as file:

        # Get keys in list
        KEYstring = file.readline()
        KEYstring = KEYstring.replace('\n', '')
        KEYSlist = list(KEYstring.split(','))
        KEYSlist.remove("name")

        file.seek(0)

        # Load data in a list of dicts
        dictreader = csv.DictReader(file)
        for row in dictreader:
            DATA.append(row)

    # Load sequence in a string
    with open(sys.argv[2], 'r') as sequence:
        listseq = sequence.readline()
        suspect = "".join(listseq)

    keycount = {}
    # Convert the KEYSlist into a dictionary
    for src in KEYSlist:
        keycount[src] = num_b2b(src, suspect)

    # Check for matches
    for person in DATA:
        matchcount = 0
        for src in KEYSlist:
            if int(person[src]) == keycount[src]:
                matchcount += 1
            if matchcount == len(keycount):
                sys.exit(f"{person['name']}")

    # If not match was found;
    sys.exit("No match")


"""
    Credits go to Mark Gritter for this function.
    See : https://bit.ly/3rStnX2
"""


def num_b2b(substring, full_string):
    pattern = "(?=((" + re.escape(substring) + ")+))"
    matches = re.findall(pattern, full_string)
    return max(len(m[0]) // len(substring) for m in matches)


if __name__ == "__main__":
    main()