#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool loop_check(int i, int initial, int count);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // go through all candidates names
    for (int i = 0; i < candidate_count; i++)
    {
        // if find name then update te vote and quit
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // go through all the ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // go through all the ranks that are loosing for the curent rank
        for (int j = i + 1; j < candidate_count; j++)
        {
            // update the preferences array
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Sets the count of pairs to
    pair_count = 0;
    // go through all the ranks that are winning for the curent rank
    for (int i = 0; i < candidate_count; i++)
    {
        // go through all the ranks that are loosing for the curent rank
        for (int j = 0; j < candidate_count; j++)
        {
            // check if a candidate is prefered
            if (preferences[i][j] > preferences[j][i])
            {
                // updates the winner of this particular pair
                pairs[pair_count].winner = i;
                // updates the loser of this particular pair
                pairs[pair_count].loser = j;
                // update the pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // bubble sort
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j < pair_count; j++)
        {
            // check if the victory of the pair is stronger than the victory of the other pair
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {
                //creates a variable that stores a value of a pair temporarily
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // go through all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // creates a variable to store if there's a loop presuming it dosen't exist
        bool loops = false;

        // pass through all the candidates to check if there's a possibility to be looped
        for (int j = 0; j < candidate_count; j++)
        {

            // check if there's a possiility of loop
            if (locked[j][pairs[i].winner] == true)
            {
                // set loops as true as indicator of a possiility of loop
                loops = true;
            }
        }

        //set the arrow pointing to check if its a valid arrow, if not then the arrow will be removed
        locked[pairs[i].winner][pairs[i].loser] = true;

        //if there's a possibility of loop
        if (loops == true)
        {
            //set the pair [i][i] to false to prevent false positives
            locked[pairs[i].winner][pairs[i].winner] = false;
            //check if actually there's a loop
            loops = loop_check(pairs[i].winner, pairs[i].winner, 0);
        }


        // if there's no loops
        if (loops == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

    }
    return;
}

//check if there's any loop
bool loop_check(int i, int initial, int count)
{
    //check if its not the first time the function is called, and if the function current state is equal to inicial state
    if (count != 0 && initial == i)
    {
        //if its not the first time and its equal, then return true
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[j][i] == true)
        {
            count++;
            if (loop_check(j, initial, count) == true)
            {
                //if the response of the retroactive function is true, then return true making a chain of trues till the first caller
                return true;
            }
        }
    }
    //if no loop return false
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // pass throug all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // creates a variable to check if there's a candidate pointing to the current candidade
        bool pointed = false;
        // creates a variable to check if the current candidade pointing to a candidate
        bool pointing = false;
        // pass throug all the candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // check if there's a arrow pointing to the current candidate
            if (locked[j][i] == true)
            {
                pointed = true;
            }
            if (locked[i][j] == true)
            {
                pointing = true;
            }
        }
        // check if the candidate is pointing to other candidate and nothing being pointed
        if (pointed == false && pointing == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
