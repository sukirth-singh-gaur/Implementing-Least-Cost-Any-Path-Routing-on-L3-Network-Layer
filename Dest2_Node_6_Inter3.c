#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b)) 

float desNode1_MidNode2(float** p){ //This function is for One Destination Node 2 Intermediate Node 1 Src Node
    /*
    printf("\n\n");
			for(int i=0; i<2; i++)
		{
			for(int j=0; j<2; j++) {
				printf("%5.2f",p[i][j]);
			}
			printf("\n");

		}
*/	
	return (1+((p[0][0])*(1-p[1][0])*(1/p[0][1]))
	        +((1-p[0][0])*(p[1][0])*(1/p[1][1]))
	        +((p[0][0])*(p[1][0])*MIN(1/p[0][1],1/p[1][1])))
	       /(1-(1-p[0][0])*(1-p[1][0]));
}


int main() {
    int n;

    // Prompt the user for the number of nodes
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Exit the program if the number of nodes is less than 1
    if (n < 1) {
        printf("Invalid number of nodes.\n");
        exit(0);
    }

    // Declare and initialize the adjacency matrix
    float mtx[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mtx[i][j] = 0; // Set all values to 0 initially
        }
    }

    // Loop to input edges and their weights (ETX values)
    while (1) {
        int from, to;
        float etx;

        // Input the starting node of the edge
        printf("Enter the nodes to connect (0 to %d) or (-1 to exit):\n", n - 1);
        printf("From node: ");
        scanf("%d", &from);

        // Exit if the user enters -1
        if (from == -1) break;

        // Input the ending node of the edge
        printf("To node: ");
        scanf("%d", &to);
        if (to == -1) break;

        // Validate the node numbers
        if (from >= n || to >= n || from < 0 || to < 0) {
            printf("Invalid node numbers. Try again.\n");
            continue;
        }

        // Input the ETX value
        printf("Enter the ETX value (> 0): ");
        scanf("%f", &etx);

        // Validate the ETX value
        if (etx <= 0) {
            printf("Invalid ETX value. Must be greater than 0.\n");
            continue;
        }

        // Assign the ETX value to the adjacency matrix
        mtx[from][to] = etx;
    }

    // Input the source node
    int s;
    printf("Enter the source node: ");
    scanf("%d", &s);

    // Validate the source node
    while (s < 0 || s >= n) {
        printf("Invalid source node. Enter again: ");
        scanf("%d", &s);
    }

    // Input the number of destination nodes
    int dNo;
    printf("Enter the number of destination nodes: ");
    scanf("%d", &dNo);

    // Declare an array for destination nodes and input them
    int d[dNo];
    for (int j = 0; j < dNo; j++) {
        printf("Enter destination node %d: ", j + 1);
        scanf("%d", &d[j]);

        // Validate the destination node
        if (d[j] < 0 || d[j] >= n) {
            printf("Invalid destination node. Enter again.\n");
            j--; // Retry the current index
        }
    }

    // Print the adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2f ", mtx[i][j]); // Print matrix values with two decimal places
        }
        printf("\n");
    }

    return 0;
}
