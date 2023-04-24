#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

const int COORDS = 1000000;
const int MAX_THREADS = 8;

int ids[MAX_THREADS];
int dotsInsideCircle = 0;

pthread_t tids[MAX_THREADS];
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


void* generateCoords(void *param) {
    int id = *(int*) param;
    int rows = COORDS;

    int step = rows/MAX_THREADS;
    int cols = 2;

    srand( (unsigned)time( NULL ) );
    double** matrix = new double*[step];
    int from = 0;
    int to = step;
    int amount = 0;

    for (int i = from; i < to; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            bool isNegative = (float) rand()/RAND_MAX < 0.5; 
            matrix[i][j] = (float) rand()/RAND_MAX * (isNegative ? -1 : 1);
        };
        isDotInsideCircle(&amount, matrix[i]);
    };
    pthread_mutex_lock(&mutex_lock);
    dotsInsideCircle += amount;
    pthread_mutex_unlock(&mutex_lock);
    pthread_exit(NULL);
};


int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex_lock, NULL);

    for (int i = 0; i < MAX_THREADS; i++) {
        ids[i] = i;
    };

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tids[i], NULL, generateCoords, (void*) &ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    cout << "Amount: " << dotsInsideCircle << "/" << COORDS << endl;

    double pi = 4.0 * dotsInsideCircle / COORDS;

    cout << "Pi is equal to: " << fixed << setprecision(5) << pi << endl;

    return 0;
};