#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double rand_num; // shared variable
pthread_mutex_t mutex;

void *generate_random(void *arg) {
    while (1) {
        double r = (double) rand() / RAND_MAX; // generate random number between 0 and 1
        pthread_mutex_lock(&mutex); // lock mutex before writing to shared variable
        rand_num = r; // write to shared variable
        pthread_mutex_unlock(&mutex); // unlock mutex
        printf("Random number: %f\n", r); // print generated random number
        sleep(1); // wait for 1 second
    }
}

void *print_random(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex); // lock mutex before reading from shared variable
        printf("Shared variable: %f\n", rand_num); // print value of shared variable
        pthread_mutex_unlock(&mutex); // unlock mutex
        sleep(1); // wait for 1 second
    }
}

int main() {
    pthread_t tid1, tid2; // thread IDs
    pthread_mutex_init(&mutex, NULL); // initialize mutex

    // create threads
    pthread_create(&tid1, NULL, generate_random, NULL);
    pthread_create(&tid2, NULL, print_random, NULL);

    // join threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex); // destroy mutex
    return 0;
}

