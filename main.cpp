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
const int THREADS = 3;
int id[THREADS];
int dotsInsideCircle = 0;
pthread_t tids[THREADS];
pthread_mutex_t mutex_lock;


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


void* generateCoords(int d) {
    int rows = COORDS;
    int cols = 2;

    srand( (unsigned)time( NULL ) );
    pthread_mutex_lock(&mutex_lock);
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            bool isNegative = (float) rand()/RAND_MAX < 0.5; 
            matrix[i][j] = (float) rand()/RAND_MAX * (isNegative ? -1 : 1);
        };
        isDotInsideCircle(&dotsInsideCircle, matrix[i]);
    };

    // printMatrix(matrix, rows);
    pthread_mutex_unlock(&mutex_lock);
    pthread_exit(NULL);
};


int main(int argc, char* argv[]) {
    // for (int i = 0; i < THREADS; i++) {
    //     state[i] = GENERATING;
    //     id[i] = i;
    //     pthread_cond_init(&chopsticks[i], NULL);
    // }
    pthread_mutex_init(&mutex_lock, NULL);

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&tids[i], NULL, generateCoords, (void*) 3);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    cout << "Amount: " << dotsInsideCircle << "/" << COORDS << endl;

    double pi = 4.0 * dotsInsideCircle / COORDS;

    cout << "Pi is equal to: " << fixed << setprecision(5) << pi << endl;

    return 0;
};