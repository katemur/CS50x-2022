import csv
import sys


def main():
    # checking for command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)
    database_file = sys.argv[1]
    seq_file = sys.argv[2]
    # opening and reading csv file as a dictionary and clising it
    with open(database_file, "r") as data:
        reader = csv.DictReader(data)
        database = list(reader)
    # opening sequence file as a list and closing it
    with open(seq_file, "r") as seq:
        sequence = seq.read()
    # computing the longest run of consecutive repeats in sequence
    max_str_counts = []
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        max_str_counts.append(1)
        # looping through the sequence to find STR
        for j in range(len(sequence)):
            STR_count = 0
            # if match is found, counting repeats
            if sequence[j:(j + len(STR))] == STR:
                k = 0
                while sequence[(j + k):(j + k + len(STR))] == STR:
                    STR_count += 1
                    k += len(STR)
                    # if new maximum of repeats is found, update max_str_counts
                    if STR_count > max_str_counts[i - 1]:
                        max_str_counts[i - 1] = STR_count
    # comparing with database
    for i in range(len(database)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            if int(max_str_counts[j - 1]) == int(database[i][reader.fieldnames[j]]):
                matches += 1
                if matches == (len(reader.fieldnames) - 1):
                    print(database[i]['name'])
                    sys.exit(0)
    print("No match")


if __name__ == "__main__":
    main()