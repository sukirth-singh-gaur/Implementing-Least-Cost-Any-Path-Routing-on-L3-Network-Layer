#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b)) // Macro to calculate the minimum of two numbers

// Function to compute cost for 1 intermediate node
float hop_2_dest_1_route_1(float** p) {
    return 1 / p[0][0] + 1 / p[0][1];
}

// Function to compute cost for 2 intermediate nodes
float hop_2_dest_1_route_2(float** p) {
    return (1 + ((p[0][0]) * (1 - p[1][0]) * (1 / p[0][1]))
            + ((1 - p[0][0]) * (p[1][0]) * (1 / p[1][1]))
            + ((p[0][0]) * (p[1][0]) * MIN(1 / p[0][1], 1 / p[1][1])))
           / (1 - (1 - p[0][0]) * (1 - p[1][0]));
}

// Function to compute cost for 3 intermediate nodes
float hop_2_dest_1_route_3(float** p) {
    return (1 + ((p[0][0]) * (1 - p[1][0]) * (1 - p[2][0]) * (1 / p[0][1]))
            + ((1 - p[0][0]) * (p[1][0]) * (1 - p[2][0]) * (1 / p[1][1]))
            + ((1 - p[0][0]) * (1 - p[1][0]) * (p[2][0]) * (1 / p[2][1]))
            + ((p[0][0]) * (p[1][0]) * (1 - p[2][0]) * MIN(1 / p[0][1], 1 / p[1][1]))
            + ((1 - p[0][0]) * (p[1][0]) * (p[2][0]) * MIN(1 / p[1][1], 1 / p[2][1]))
            + ((p[0][0]) * (1 - p[1][0]) * (p[2][0]) * MIN(1 / p[0][1], 1 / p[2][1]))
            + ((p[0][0]) * (p[1][0]) * (p[2][0]) * MIN(1 / p[2][1], MIN(1 / p[0][1], 1 / p[1][1]))))
           / (1 - (1 - p[0][0]) * (1 - p[1][0]) * (1 - p[2][0]));
}

// Recursive function to generate combinations of intermediate nodes
void generate_combinations(int* intermediates, int idx, int* current_set, int current_size, int num_nodes, int** combinations, int* combo_count) {
    if (idx == num_nodes) {
        if (current_size > 0) { // Only store non-empty combinations
            for (int i = 0; i < current_size; i++) {
                combinations[*combo_count][i] = current_set[i];
            }
            (*combo_count)++;
        }
        return;
    }
    generate_combinations(intermediates, idx + 1, current_set, current_size, num_nodes, combinations, combo_count);
    current_set[current_size] = intermediates[idx];
    generate_combinations(intermediates, idx + 1, current_set, current_size + 1, num_nodes, combinations, combo_count);
}

// Function to find the minimum cost
void find_min_cost(int num_nodes, int source, int dest, float** prob_matrix) {
    int intermediates[num_nodes];
    int intermediates_count = 0;

    // Collect intermediate nodes
    for (int i = 0; i < num_nodes; ++i) {
        if (i != source && i != dest) {
            intermediates[intermediates_count++] = i;
        }
    }

    int max_combos = (1 << intermediates_count); // Maximum number of combinations
    int** combinations = (int**)malloc(max_combos * sizeof(int*));
    for (int i = 0; i < max_combos; ++i) {
        combinations[i] = (int*)calloc(intermediates_count, sizeof(int));
    }

    int combo_count = 0;
    int* current_set = (int*)malloc(intermediates_count * sizeof(int));
    generate_combinations(intermediates, 0, current_set, 0, intermediates_count, combinations, &combo_count);

    float min_cost = (float)INT_MAX;
    int min_cost_combination = -1;

    // Evaluate cost for each combination
    for (int i = 0; i < combo_count; ++i) {
        int combo_size = 0;
        while (combo_size < intermediates_count && combinations[i][combo_size] != 0) combo_size++;

        float** p = (float**)malloc(combo_size * sizeof(float*));
        for (int j = 0; j < combo_size; ++j) {
            p[j] = (float*)malloc(2 * sizeof(float));
        }

        // Populate probability matrix for the combination
        for (int j = 0; j < combo_size; ++j) {
            int node = combinations[i][j];
            p[j][0] = prob_matrix[source][node];  // Source to intermediate
            p[j][1] = prob_matrix[node][dest];    // Intermediate to destination
        }

        float cost = 0;
        if (combo_size == 1) {
            cost = hop_2_dest_1_route_1(p);
        } else if (combo_size == 2) {
            cost = hop_2_dest_1_route_2(p);
        } else if (combo_size == 3) {
            cost = hop_2_dest_1_route_3(p);
        }

        // Update minimum cost
        if (cost < min_cost) {
            min_cost = cost;
            min_cost_combination = i;
        }

        for (int j = 0; j < combo_size; ++j)
            free(p[j]);
        free(p);
    }

    // Output result
    printf("Minimum cost is: %.6f for combination {", min_cost);
    for (int j = 0; j < intermediates_count; ++j) {
        if (combinations[min_cost_combination][j] != 0) {
            printf("%d", combinations[min_cost_combination][j]);
            if (j + 1 < intermediates_count && combinations[min_cost_combination][j + 1] != 0) {
                printf(", ");
            }
        }
    }
    printf("}\n");

    // Free allocated memory
    for (int i = 0; i < max_combos; ++i) {
        free(combinations[i]);
    }
    free(combinations);
    free(current_set);
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    while (n < 2) {
        printf("\nEnter number of nodes again: ");
        scanf("%d", &n);
    }

    float** mtx = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        mtx[i] = (float*)calloc(n, sizeof(float));
    }

    // Read probability values for edges
    printf("Enter nodes to connect (-1 to exit):\n");
    while (1) {
        int from, to;
        float prob;
        printf("From node: ");
        scanf("%d", &from);
        if (from == -1) break;
        printf("To node: ");
        scanf("%d", &to);
        if (to == -1) break;
        printf("Probability: ");
        scanf("%f", &prob);
        mtx[from][to] = prob;
    }

    // Source and destination nodes
    int source, dest;
    printf("Enter source node: ");
    scanf("%d", &source);
    printf("Enter destination node: ");
    scanf("%d", &dest);

    find_min_cost(n, source, dest, mtx);

    for (int i = 0; i < n; ++i) {
        free(mtx[i]);
    }
    free(mtx);
    return 0;
}
