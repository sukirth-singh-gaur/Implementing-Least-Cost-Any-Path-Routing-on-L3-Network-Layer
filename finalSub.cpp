#include <iostream>
#include <vector>
#include <iomanip> // For std::setprecision
#include <limits>  // For input validation
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// Function to compute the cost for one destination node with two intermediate nodes
float hop_2_dest_1_route_2(vector<float> &p) {
    float x = 0.00;
    x = (1 - 1 /p[0] - 1 /p[1] + 1/(p[0] * p[1])
        +((1 - 1/p[0]) * (1/p[1]) *(1 + p[3]))
        +((1/p[0]) * (1 - 1/p[1]) * (1 + p[2]))
        +((1/p[0]) * (1/p[1]) * (1 + min(p[2],p[3]))))/(1 /p[0] + 1/p[1] - 1/(p[0] * p[1]));
    return x;
}

float dest2(vector<float> &p){                       
    float x = 0.00;
    x = (1 - 1 /p[0] - 1 /p[1] + 1/(p[0] * p[1])
        +((1 - 1/p[0]) * (1/p[1]) * (1 + p[0]))
        +((1/p[0]) * (1 - 1/p[1]) * (1 + p[1]))
        +((1/p[0]) * (1/p[1]) * (1))) / (1 /p[0] + 1/p[1] - 1/(p[0] * p[1]));
    return x;
}

float dest2_MidNode3(vector<vector<float>> &m){
    float x = 0.0;

    vector<float> cost0_4 = {m[0][1],m[0][2],m[1][4],m[2][4]};
    vector<float> cost0_5 = {m[0][2],m[0][3],m[2][5],m[3][5]};
    vector<float> cost2_45 = {m[2][4],m[2][5]};  

    x = (1 - 1 / m[0][3] - 1 / m[0][2] + 1 / ( m[0][2] * m[0][3]) - 1 / m[0][1] + 1 / (m[0][1] * m[0][3]) + 1 / (m[0][1] * m[0][2]) - 1 / (m[0][1] * m[0][2] * m[0][3])
        +((1 - 1/m[0][1]) * (1 - 1/m[0][2]) * (1/m[0][3]) * (1 + m[3][5] + hop_2_dest_1_route_2(cost0_4)))
        +((1 - 1/m[0][1]) * (1/m[0][2]) * (1 - 1/m[0][3]) * (1 + dest2(cost2_45)))
        +((1/m[0][1])  * (1 - 1/m[0][2]) * (1 - 1/m[0][3]) * (1 + m[1][4] + hop_2_dest_1_route_2(cost0_5)))
        +((1 - 1/m[0][1]) * (1/m[0][2]) * (1/m[0][3]) * (1+min(dest2(cost2_45),(m[2][4] + m[3][5]))))
        +((1/m[0][1]) * (1/m[0][2]) * (1 - 1/m[0][3]) * (1+min(dest2(cost2_45),(m[1][4] + m[2][5]))))
        +((1/m[0][1]) * (1 - 1/m[0][2]) * (1/m[0][3]) * (1 + m[1][4] + m[3][5]))
        +((1/m[0][1]) * (1/m[0][2]) * (1/m[0][3]) * (1 + min(min(m[1][4] + m[3][5],min(m[1][4]+m[2][5],m[2][4] + m[3][5])), (dest2(cost2_45)))))) 
        / (1 / m[0][3] + 1 / m[0][2] - 1/(m[0][3]* m[0][2]) + 1 / m[0][1] - 1 /(m[0][1] * m[0][3]) - 1 /(m[0][1] * m[0][2]) + 1/(m[0][1] * m[0][2] * m[0][3]));
    
    return x;
}

int main() {
    char c;
    cout << "Would You Like to Take input MTX from input.txt? (Y/N): ";
    cin >> c;

    vector<vector<float>> mtx;

    if (c == 'Y') {
        ifstream inputFile("input.txt");
        if (!inputFile) {
            cerr << "Error: Unable to open file!" << endl;
            return 1;
        }

        int rows, cols;
        inputFile >> rows >> cols; 

        mtx.assign(rows, vector<float>(cols)); 

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                inputFile >> mtx[i][j];
            }
        }

        inputFile.close();
    } else if (c == 'N') {
        int n;
        cout << "Enter number of nodes: ";
        cin >> n;

        if (n < 1) {
            cout << "Invalid number of nodes.\n";
            return 0;
        }

        mtx.assign(n, vector<float>(n, 0));

        while (true) {
            int from, to;
            float etx;
            cout << "Enter the nodes to connect (0 to " << n - 1 << ") or (-1 to exit):\n";
            cout << "From node: ";
            cin >> from;

            if (from == -1) break;

            cout << "To node: ";
            cin >> to;
            if (to == -1) break;

            if (from >= n || to >= n || from < 0 || to < 0) {
                cout << "Invalid node numbers. Try again.\n";
                continue;
            }

            cout << "Enter the ETX value (> 0): ";
            cin >> etx;

            if (etx <= 0) {
                cout << "Invalid ETX value. Must be greater than 0.\n";
                continue;
            }

            mtx[from][to] = etx;
            mtx[to][from] = etx;
        }
    } else {
        cout << "Enter Y or N" << endl;
        return 1;
    }

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create output.txt!" << endl;
        return 1;
    }

    vector<float> cost0_4 = {mtx[0][1], mtx[0][2], mtx[1][4], mtx[2][4]};
    vector<float> cost0_5 = {mtx[0][2], mtx[0][3], mtx[2][5], mtx[3][5]};
    vector<float> cost2_45 = {{mtx[2][4], mtx[2][5]}};
    outputFile << "Source  Intermediate  Destination  Cost"<<endl;
    outputFile << "  (0)      (1,2)          (4)      " << hop_2_dest_1_route_2(cost0_4) << endl;
    outputFile << "  (0)      (2,3)          (5)      " << hop_2_dest_1_route_2(cost0_5) << endl;
    outputFile << "  (2)        ()          (4,5)     " << dest2(cost2_45) << endl;
    outputFile << "  (0)     (1,2,3)        (4,5)     " << dest2_MidNode3(mtx) << endl;

    outputFile.close();
    cout << "Results written to output.txt" << endl;

    return 0;
}
