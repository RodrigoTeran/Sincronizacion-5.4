#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>

using namespace std;

const int COORDS = 10;

void generateCoords() {

};

void printMatrix(double** matrix, int rows) {
    cout << "Printing matrix..." << endl;
    for (int i = 0; i < rows; i++) {
        cout << "(" << fixed << setprecision(5) << matrix[i][0] << ", " << fixed << setprecision(5) << matrix[i][1] << ")" << endl;
    };
};

int main() {
    int rows = COORDS, cols = 2;
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 3.123456789;
        }
    }
    printMatrix(matrix, rows);
    // cout << matrix[i] << endl;

    return 0;
};