#include <iostream>
#include <vector>
#include <iomanip> // For std::setprecision
#include <limits>  // For input validation
#include<bits/stdc++.h>
using namespace std;
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Function to compute the cost for one destination node with two intermediate nodes
float desNode1_MidNode2(const std::vector<std::vector<float>>& p) {
    return (1 + (p[0][0] * (1 - p[1][0]) * (1 / p[0][1])) +
            ((1 - p[0][0]) * p[1][0] * (1 / p[1][1])) +
            (p[0][0] * p[1][0] * MIN(1 / p[0][1], 1 / p[1][1]))) /
           (1 - (1 - p[0][0]) * (1 - p[1][0]));
}

float cost_of_2_Node_path(int node1,int node2,vector<vector<float>> &mtx){
    vector<vector<float>> probMat;
    if(node1==1 && node2 ==2)
    probMat = {{mtx[0][1],mtx[1][4]},
              {mtx[0][3],mtx[3][5]}};
    else if(node1==2 && node2 ==3)
    probMat = {{mtx[0][2],mtx[2][5]},
               {mtx[0][3],mtx[3][5]}};
    return desNode1_MidNode2(probMat);
}
/*
    For Map 
               1 --- 4
              |     |    
             0 --- 2
              \     \
               3 --- 5

*/
float dest2_MidNode3(vector<vector<float>> &mtx){
    float x =  ((1 - 1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 - 1 / mtx[0][3]) * (1 + x)
              + ((1 - 1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 / mtx[0][3])) * (1 + mtx[3][4] + cost_of_2_Node_path(1,2,mtx))
              + ((1 - 1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 - 1 / mtx[0][3])) * (1 + mtx[2][4] + min(mtx[2][5],mtx[3][5]))
              + ((1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 - 1 / mtx[0][3])) * (1 + mtx[1][4] + cost_of_2_Node_path(2,3,mtx))
              + ((1 / mtx[0][1]) * (1 - 1 / mtx[0][2]) * (1 / mtx[0][3])) * (1 + mtx[1][4] + mtx[3][5])  
              + ((1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 - 1 / mtx[0][3])) * (1 + mtx[2][5] + min(mtx[1][4],mtx[2][4]))
              + ((1 / mtx[0][1]) * (1 / mtx[0][2]) * (1 / mtx[0][3])) * (1 + min(mtx[1][4],mtx[2][4]) + min(mtx[2][5],mtx[3][5])));

    return x;
}


int main() {
    int n;

    // Prompt the user for the number of nodes
    std::cout << "Enter number of nodes: ";
    std::cin >> n;

    // Exit the program if the number of nodes is less than 1
    if (n < 1) {
        std::cout << "Invalid number of nodes.\n";
        return 0;
    }

    // Declare and initialize the adjacency matrix using a 2D vector
    std::vector<std::vector<float>> mtx(n, std::vector<float>(n, 0));

    // Loop to input edges and their weights (ETX values)
    while (true) {
        int from, to;
        float etx;

        // Input the starting node of the edge
        std::cout << "Enter the nodes to connect (0 to " << n - 1 << ") or (-1 to exit):\n";
        std::cout << "From node: ";
        std::cin >> from;

        // Exit if the user enters -1
        if (from == -1) break;

        // Input the ending node of the edge
        std::cout << "To node: ";
        std::cin >> to;
        if (to == -1) break;

        // Validate the node numbers
        if (from >= n || to >= n || from < 0 || to < 0) {
            std::cout << "Invalid node numbers. Try again.\n";
            continue;
        }

        // Input the ETX value
        std::cout << "Enter the ETX value (> 0): ";
        std::cin >> etx;

        // Validate the ETX value
        if (etx <= 0) {
            std::cout << "Invalid ETX value. Must be greater than 0.\n";
            continue;
        }

        // Assign the ETX value to the adjacency matrix
        mtx[from][to] = etx;
    }

    // Input the source node
    int s;
    std::cout << "Enter the source node: ";
    std::cin >> s;

    // Validate the source node
    while (s < 0 || s >= n) {
        std::cout << "Invalid source node. Enter again: ";
        std::cin >> s;
    }

    // Input the number of destination nodes
    int dNo;
    std::cout << "Enter the number of destination nodes: ";
    std::cin >> dNo;

    // Declare a vector for destination nodes and input them
    std::vector<int> destNodes(dNo);
    for (int j = 0; j < dNo; j++) {
        std::cout << "Enter destination node " << j + 1 << ": ";
        std::cin >> destNodes[j];

        // Validate the destination node
        if (destNodes[j] < 0 || destNodes[j] >= n) {
            std::cout << "Invalid destination node. Enter again.\n";
            j--; // Retry the current index
        }
    }

    // Print the adjacency matrix
    std::cout << "\nAdjacency Matrix:\n";
    for (const auto& row : mtx) {
        for (const auto& value : row) {
            if (value == 0)
                std::cout << std::setw(6) << "0.00"; // Print zero values
            else
                std::cout << std::setw(6) << std::fixed << std::setprecision(2) << value;
        }
        std::cout << '\n';
    }

    float minCost = dest2_MidNode3(mtx);

    cout<<"The Min Cost For 2 Destination Nodes and 3 Intermediate Nodes is: "<<minCost<<endl;

    return 0;
}
