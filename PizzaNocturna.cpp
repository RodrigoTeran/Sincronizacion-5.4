#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_STUDENTS = 10;
const int MAX_SLEEP_TIME = 5;
const int MAX_THREADS = 8;
enum{STUDYING,EATING}state[MAX_STUDENTS];

int ids[MAX_THREADS];

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

void test(int i) {
    if (state[i] == EATING &&
        state[i] == STUDYING) {

        state[i] = EATING;
        pthread_cond_signal(&chopsticks[i]);
    }
}



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