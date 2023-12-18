import csv
import sys


def main():

    # check if there's the correct number of arguments
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    # open the csv file
    file = open(sys.argv[1])
    type(file)
    # starts to read the csv file
    csvreader = csv.reader(file)
    # creates a variable to store the header value where there's the sequences of dna
    header = []
    # makes the header variable store the header from the csv file
    header = next(csvreader)

    # starts a variable dna with will contein all data of the csv file
    dna = []
    # apend all the data to dna
    for row in csvreader:
        dna.append(row)
    file.close()
    # read the txt file and stores the sequence from that file on  a sequence variable
    with open(sys.argv[2]) as f:
        sequence = f.readlines()
    f.close()
    # creates a list to store every longest match for each sequence
    longests = []
    # get the longest match for each sequence
    for i in header:
        # check if its a sequence
        if i != "name":
            longests.append(longest_match(sequence[0], i))
    # go through all the dna list to find a match
    for i in dna:
        # assume that there's a match until proven there's not
        check = True
        j = 0
        # loop through all the dna subsequences
        while j < len(longests):
            # check if it still matching
            if int(i[j + 1]) != int(longests[j]):
                # if it's not matching change check to false
                check = False
                break
            j += 1
        # check if it still matching on the final
        if check == True:
            # if it still matching print the names
            print(i[0])
            return

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
