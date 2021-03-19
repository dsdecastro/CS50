// The starter code provided by course instructors can be found at https://cdn.cs50.net/2020/fall/psets/3/tideman/tideman.c
// I (Daniel de Castro) implemented all the functions listed in the fuction prototypes
// Of note: the following functions were implemented in an attempt to perform a depth-first search of the directed graph
// represeted by the locked[][] array: is_cyclical(void), find_first_vertex(void), traverse(int start_vertex), cycle_detected(void)

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

// For the depth-first search to see if graph is cyclical as part of the implementation of lock_pairs()
int stack[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int stack_index;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool validate_candidate(string name);
int candidate_index(string name);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool margin_less_than(int i, int j);
void lock_pairs(void);
bool is_cyclical(void);
int find_first_vertex(void);
void traverse(int start_vertex);
bool cycle_detected(void);
void print_winner(void);

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
    // Check if the name supplied is a valid candidate, and then update the ranks array
    if (validate_candidate(name))
    {
        ranks[rank] = candidate_index(name);
        return true;
    }

    return false;
}

// Check if a candidate is in the list of candidates
bool validate_candidate(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            return true;
        }
    }

    return false;
}

// Get the index of a given candidate in the candidates array
int candidate_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through the ranks array and a
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initialize pair_count
    pair_count = 0;

    // Loop through preferences array
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If candidate at index i beats that at index j, update pairs
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // If candidate at index i loses to that at index j, update pairs
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initialize a holder variable
    int highest_index = 0;
    pair temp;
    temp.winner = 0;
    temp.loser = 0;

    // Perform a selection sort on pairs
    for (int i = 0; i < pair_count - 1; i++)
    {
        highest_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (margin_less_than(highest_index, j))
            {
                highest_index = j;
            }
        }

        if (highest_index != i)
        {
            temp = pairs[i];
            pairs[i] = pairs[highest_index];
            pairs[highest_index] = temp;
        }
    }

    return;
}

// Compare the margins of victory of two pairs,
// returning true if the margin of victory of the second pair is greater
bool margin_less_than(int i, int j)
{
    int margin1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    int margin2 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

    return margin1 < margin2;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Initialize winner and loser variables to be used in the loop
    int winner = 0;
    int loser = 0;

    // Loop through sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        // Lock the edge
        locked[winner][loser] = true;
        // Now check to see if the graph would be made cyclical with the addition of this new edge
        if (is_cyclical())
        {
            // If so, unlock the edge
            locked[winner][loser] = false;
        }
    }

    return;
}

// Perform a depth-first search of the candidate graph for cycles
bool is_cyclical(void)
{
    for (int i = 1; i < 19; i++)
    {
        stack[i] = -1;
    }
    stack_index = 0;

    // Set the first value of the stack to the starting vertex
    stack[0] = find_first_vertex();
    // Check to make sure that there are any existing edges in the graph
    if (stack[0] < 0)
    {
        return false;
    }

    // Begin the recursive search
    traverse(stack[0]);

    return cycle_detected();
}

// Find a vertex with which to begin is_cyclical search
int find_first_vertex(void)
{
    // Search for an existing locked edge
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                return i;
            }
        }
    }

    // Return -1 if there are no locked edges yet
    return -1;
}

// Recursively explore all the possible paths on the graph
void traverse(int start_vertex)
{
    // Check to see if a cycle was already detected to avoid unnecessary work
    if (!cycle_detected())
    {
        stack[stack_index] = start_vertex;
        stack_index++;

        for (int i = 0; i < candidate_count; i++)
        {
            // Find all the edges stemming away from this vertex, and traverse those edges
            if (i != start_vertex && locked[start_vertex][i])
            {
                traverse(i);
            }
        }
    }
}

// Check to see if any vertex was recorded twice in the stack; if so, return true: the graph is cyclical
bool cycle_detected(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < 19; j++)
        {
            if (stack[i] == stack[j] && stack[i] >= 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Loop through the 2-D array representing the locked graph
    bool is_recipient = false;
    for (int i = 0; i < candidate_count; i++)
    {
        is_recipient = false;
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if the candidate i has already been identified as the recipient of a directed edge,
            // or if the edge from candidate j to candidate i has been locked
            if (!is_recipient && locked[j][i])
            {
                // If these conditions are met, note that candidate i is the recipient of a directed edge
                is_recipient = true;
            }
        }

        // If candidate i is not the recipient of a directed edge, print that candidate as the winner of the election
        if (!is_recipient)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    return;
}
