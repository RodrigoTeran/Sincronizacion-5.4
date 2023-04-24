#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <cstdlib>

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
    srand( (unsigned)time( NULL ) );
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            bool isNegative = (float) rand()/RAND_MAX < 0.5; 
            matrix[i][j] = (float) rand()/RAND_MAX * (isNegative ? -1 : 1);
        }
    }
    printMatrix(matrix, rows);

    return 0;
};