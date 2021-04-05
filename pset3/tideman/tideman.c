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
int get_margin(int pair_index);
bool check_cycle(int stop, int origin);

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
    int candidate_index;
    for (int i = 0; i < candidate_count; i++)
    {
        /*
        Checks through the candidates array, and uses the index at which the
        name was found to identify the candidate in the ranks array.
        */
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

//Returns index of specified element in the Ranks[] array
int get_index(int element, int ranks[])
{
    int index;
    for (int i = 0; i < candidate_count; i++)
    {
        if (element == ranks[i])
        {
            index = i;
        }
    }
    return index;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (get_index(i, ranks) < get_index(j, ranks))
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

//Gets the margin of victory between two candidates of the given pair
int get_margin(int pair_index)
{
    return preferences[pairs[pair_index].winner][pairs[pair_index].loser] - 
           preferences[pairs[pair_index].loser][pairs[pair_index].winner];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair most = pairs[i];
        for (int j = i + 1; j < pair_count; j++)
        {
            if (get_margin(j) > get_margin(i))
            {
                most = pairs[j];
                pair temp = pairs[i];
                pairs[i] = most;
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!check_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

//FUCK THIS OMG I AM SO DONE FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK FUCK
bool check_cycle(int stop, int origin)
{
    if (stop == origin)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[stop][i])
        {
            if (check_cycle(i, origin))
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
    for (int i = 0; i < candidate_count; i++)
    {
        int counted = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] != true)
            {
                counted++;
                if (counted == candidate_count)
                {
                    printf("\nWinner: %s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

/*
I am sorry to the future me who will have to figure out this trash ass code I wrote 
without any comments explaining whatever this shit does
*/
