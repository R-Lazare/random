#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5
#define ARRAY_SIZE 10

typedef struct {
    int start;
    int end;
    int *array;
    pthread_mutex_t *data_mutex;
    sem_t *semaphores;
    int index;
} ThreadArgs;

void *thread_function(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    sem_wait(&args->semaphores[args->index]);

    pthread_mutex_lock(args->data_mutex);  // Lock mutex to protect data

    printf("Thread %d: start = %d, end = %d\n", (int)pthread_self(), args->start, args->end);
    for (int i = args->start; i < args->end; i++) {
        args->array[i] = i * i;
    }

    pthread_mutex_unlock(args->data_mutex);  // Unlock mutex after data modification

    if(args->index < NUM_THREADS - 1) {
        sem_post(&args->semaphores[args->index + 1]);
    }

    pthread_exit(NULL);
}

int main() {
    int array[ARRAY_SIZE];
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    sem_t semaphores[NUM_THREADS];
    pthread_mutex_t data_mutex;

    pthread_mutex_init(&data_mutex, NULL);
    sem_init(&semaphores[0], 0, 1);  // First semaphore is available
    for (int i = 1; i < NUM_THREADS; i++) {
        sem_init(&semaphores[i], 0, 0);  // Others are unavailable
    }

    int chunkSize = ARRAY_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = i * chunkSize;
        args[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunkSize;
        args[i].array = array;
        args[i].data_mutex = &data_mutex;
        args[i].semaphores = semaphores;
        args[i].index = i;

        pthread_create(&threads[i], NULL, thread_function, (void *)&args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        sem_destroy(&semaphores[i]);
    }
    pthread_mutex_destroy(&data_mutex);

    printf("Resulting array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
