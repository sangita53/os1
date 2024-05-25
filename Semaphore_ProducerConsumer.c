#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define N 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t s, empty, full;

void produce_item(int item) {
    printf("Producing item: %d\n", item);
}

void consume_item(int item) {
    printf("Consuming item: %d\n", item);
}

void *producer(void *arg) {
    for (int i = 0; i < N; ++i) {
        int item = i + 1;

        produce_item(item);

        sem_wait(&empty);
        sem_wait(&s);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&s);
        sem_post(&full);

        usleep(500000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < N; ++i) {
        sem_wait(&full);
        sem_wait(&s);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&s);
        sem_post(&empty);

        consume_item(item);

        usleep(1000000);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&s, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&s);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}