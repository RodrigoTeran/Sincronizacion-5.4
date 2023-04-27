#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

const int STUDENTS = 10;
const int MAX_THREADS = 8;
const int SLICES_PER_PIZZA = 8;
const int SLEEP_TIME = 1;
enum{
    STUDYING_AND_EATING,
    WAITING
} state[STUDENTS];

int ids[STUDENTS];
int slices = SLICES_PER_PIZZA;

pthread_t tids[MAX_THREADS];
pthread_cond_t areSlicesLeft;
pthread_mutex_t mutex_lock_slices, mutex_lock_pizzeria;


void waiting(int id) {
    sleep(SLEEP_TIME);
}

void eating(int id) {
    cout << "Student: " << id << " is eating." << endl;
    sleep(SLEEP_TIME);
}

void askForSlices(int id) {
    cout << "Student: " << id << " is asking for another slice..." << endl;
    sleep(SLEEP_TIME);
}

void test(int i) {
    // Try to eat
    if (state[i] == WAITING &&
        slices > 0
    ) {
        state[i] = STUDYING_AND_EATING;
        cout << " Slices left: " << slices << endl;
        slices -= 1;
        return;
    }
    if (slices == 0) {
        askForSlices(i);
        pthread_mutex_unlock(&mutex_lock_pizzeria);
        slices = SLICES_PER_PIZZA;
        pthread_mutex_lock(&mutex_lock_pizzeria);
        pthread_cond_signal(&areSlicesLeft);
        test(i);
    }
}

void pickupSliceOfPizza(int i) {
    pthread_mutex_lock(&mutex_lock_slices);
    test(i);
    // If it is still waiting we need to wait until there are more slices
    while (state[i] == WAITING) {
        pthread_cond_wait(&areSlicesLeft, &mutex_lock_slices);
    }
    pthread_mutex_unlock(&mutex_lock_slices);
}

void finishEating(int i) {
    pthread_mutex_lock(&mutex_lock_slices);
    state[i] = WAITING;
    pthread_mutex_unlock(&mutex_lock_slices);
}

void* student(void *param) {
    int id = *((int*) param);

    while(true) {
        waiting(id);
        pickupSliceOfPizza(id);
        eating(id);
        finishEating(id);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < STUDENTS; i++) {
        state[i] = WAITING;
        ids[i] = i;
    }
    pthread_cond_init(&areSlicesLeft, NULL);
    pthread_mutex_init(&mutex_lock_slices, NULL);

    pthread_mutex_init(&mutex_lock_pizzeria, NULL);
    pthread_mutex_lock(&mutex_lock_pizzeria);

    for (int i = 0; i < STUDENTS; i++) {
        pthread_create(&tids[i], NULL, student, (void*) &ids[i]);
    }

    for (int i = 0; i < STUDENTS; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}
