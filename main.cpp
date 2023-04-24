#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

const int COORDS = 3000;

void printMatrix(double** matrix, int rows) {
    cout << "Printing matrix..." << endl;
    for (int i = 0; i < rows; i++) {
        cout << "(" << fixed << setprecision(5) << matrix[i][0] << ", " << fixed << setprecision(5) << matrix[i][1] << ")" << endl;
    };
};


void isDotInsideCircle(int* amount, double* dot) {
    double distance = pow(pow(dot[0], 2) + pow(dot[1], 2), .5);

    if (distance > 1) return;

    // Its inside
    *amount += 1;
};


void generateCoords(int rows, int* dotsInsideCircle) {
    int cols = 2;

    srand( (unsigned)time( NULL ) );
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            bool isNegative = (float) rand()/RAND_MAX < 0.5; 
            matrix[i][j] = (float) rand()/RAND_MAX * (isNegative ? -1 : 1);
        }
        isDotInsideCircle(dotsInsideCircle, matrix[i]);
    }
    // printMatrix(matrix, rows);  
};


int main() {
    // Create matrix
    int dotsInsideCircle = 0;

    generateCoords(COORDS, &dotsInsideCircle);

    cout << "Amount: " << dotsInsideCircle << "/" << COORDS << endl;

    double pi = 4.0 * dotsInsideCircle / COORDS;

    cout << "Pi is equal to: " << fixed << setprecision(5) << pi << endl;

    return 0;
};