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
    // Loop through the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate matches the given vote name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increase the candidate's votes and return
            candidates[i].votes++;
            return true;
        }
    }

    // Return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Perform a selection sort on the candidates' vote totals

    // Initialize a temporary candidate to allow us to swap places in the array
    candidate temp;
    temp.name = "";
    temp.votes = 0;

    // Initialize a holder for the index with the candidate with the most votes
    int highest_index = 0;

    // Perform the selection sort
    for (int i = 0; i < candidate_count - 1; i++)
    {
        highest_index = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[highest_index].votes < candidates[j].votes)
            {
                highest_index = j;
            }
        }
        temp = candidates[i];
        candidates[i] = candidates[highest_index];
        candidates[highest_index] = temp;
    }

    // Print out the winners of the election
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[0].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}