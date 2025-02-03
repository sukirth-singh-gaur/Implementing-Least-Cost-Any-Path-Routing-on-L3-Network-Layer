#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream inputFile("input.txt");  // Open file
    if (!inputFile) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    float rows, cols;
    inputFile >> rows >> cols; // Read matrix dimensions

    vector<vector<float>> matrix(rows, vector<float>(cols)); // Initialize matrix

    // Read the matrix from the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close(); // Close the file

    // Display the parsed matrix
    cout << "Parsed Matrix:" << endl;
    for (const auto& row : matrix) {
        for (float num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
