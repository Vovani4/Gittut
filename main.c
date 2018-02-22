#include <stdio.h>
#include <stdbool.h>

#define N 3
#define M 10


int min(int a, int b)
{
    return a<b ? a : b;
}

bool is_legal_boat(int A[][N], int weights[],
                   int assignment[], int animal, int boat)
{
    int weights_on_boat = 0;
    for (int i=0; i < animal; i++)
    {
        if (assignment[i] != boat)
            continue;
        if (!A[animal][i])
            return false;
        weights_on_boat += weights[i];
    }
    return (weights_on_boat + weights[animal]) <= M;
}

int assign_boats_aux(int A[][N], int weights[],
                     int assignment[], int animal, int last_boat)
{
    if (animal == N)
        return last_boat;
    int res = N;
    for (int i=1; i<=last_boat; i++) {
        if (is_legal_boat(A, weights, assignment, animal,
                          i))
        {
            assignment[animal] = i;
            int curr_res = assign_boats_aux(A, weights,
                                            assignment, animal+1, last_boat);
            res = min(res, curr_res);
        }
    }
    int new_boat = last_boat + 1;
    assignment[animal] = new_boat;
    int new_boat_res = assign_boats_aux(A, weights,
                                        assignment, animal+1, new_boat);
    return min(res, new_boat_res);
}
int assign_boats(int A[][N], int weights[])
{
    int assignment[N] = {0};
    return assign_boats_aux(A, weights, assignment, 0,
                            0);
}

int main() {
    int weights[N] = {3, 4, 10};
    int A[][N] = {(1,0,1), (0,1,1),(1,1,1)};
    printf("min boats for those animals: %d", assign_boats(A, weights));
    return 0;
}