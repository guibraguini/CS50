#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop trough all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if input name is valid
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Update the candidate votes
            candidates[i].votes++;
            return true;
        }

    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Create a variable to store the biggest vote result
    int biggestVote = 0;

    // Loop trough all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate have more votes then the previous candidates
        if (biggestVote < candidates[i].votes)
        {
            // If it has more votes then biggestVote recive the same value as the number of votes it have
            biggestVote = candidates[i].votes;
        }
    }

    // Loop again trough all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate have the same number of votes then the biggestVote value
        if (biggestVote == candidates[i].votes)
        {
            // If it has the same value then the candidate gets printed as winner
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
