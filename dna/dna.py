import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    # TODO: Read database file into a variable
    db = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        headers = reader.fieldnames[1:]
        for row in reader:
            db.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        sample_reader = csv.reader(file)
        for line in sample_reader:
            sample = line

    # TODO: Find longest match of each STR in DNA sequence
    STR_count = {}
    for seq in headers:
        STR_count[seq] = longest_match(str(sample), seq)

    # TODO: Check database for matching profiles
    found = False
    count = 0
    i = 0
    while i < len(db):
        # Going through STRs and checking
        for j in range(0, len(headers)):
            if int(STR_count[headers[j]]) == int(db[i][headers[j]]):
                count += 1
                if count == len(headers):
                    found = True
                    print(db[i]['name'])
                    break
        i += 1
        count = 0

    if found == False:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
