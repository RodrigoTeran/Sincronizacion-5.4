#include <iostream>

using namespace std;

const int COORDS = 10;

void generateCoords() {

};

void printMatrix(int** matrix, int rows) {
    cout << "Printing matrix..." << endl;
    for (int i = 0; i < rows; i++) {
        cout << "(" << matrix[i][0] << ", " << matrix[i][1] << ")" << endl;
    };
};

int main() {
    int rows = COORDS, cols = 2;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 3;
        }
    }
    printMatrix(matrix, rows);
    // cout << matrix[i] << endl;

    return 0;
};