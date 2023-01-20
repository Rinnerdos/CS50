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
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Candidate [%i] is preffered over candidate [%i] %i times\n", i, j, preferences[i][j]);
        }
    }
    */
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            //printf("rank[%i] = %i\n", i, rank);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //printf("preferences[%i][%i] updated\n", ranks[i], ranks[j]);
            //printf("Rank i = %i, Rank j = %i\n", i, j);
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
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    printf("Pair count is: %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair sorted_pairs[pair_count];
    int victory_strength[pair_count];
    printf("Unsorted array: ");
    for (int i = 0; i < pair_count; i++)
    {
        victory_strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        printf(" %i", victory_strength[i]);
    }
    printf("\n");
    // Sort by victory strength
    for (int i = 0; i < pair_count; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (victory_strength[j] > victory_strength[max_index])
            {
                max_index = j;
            }
        }
        int swap = victory_strength[i];
        pair swap_pair = pairs[i];
        
        victory_strength[i] = victory_strength[max_index];
        victory_strength[max_index] = swap;
        
        pairs[i] = pairs[max_index];
        pairs[max_index] = swap_pair;
    }
       
    
    printf("The sorted array should be: ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i", victory_strength[i]);
    }
    printf("\n");
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    if (pair_count > 0)
    {
        locked[pairs[0].winner][pairs[0].loser] = true;
    }

    for (int i = 1; i < pair_count; i++)
    {
        bool cycle = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[pairs[i].loser][j])
            {
                cycle = true;
                break;
            }
        }

        //check if adding this node will create a cycle
        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("True ");
            }
            else
            {
                printf("False ");
            }
        }
        printf("\n");
    }
    */
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        int i = 0;
        while (locked[i][j] != true)
        {
            if (i == candidate_count - 1)
            {
                printf("The winner is: %s\n", candidates[j]);
                return;
            }
            i++;
        }
    }
    return;
}

