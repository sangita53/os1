#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define N 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t buffer_mutex;

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

        pthread_mutex_lock(&buffer_mutex);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);

        usleep(500000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < N; ++i) {
        pthread_mutex_lock(&buffer_mutex);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);

        consume_item(item);

        usleep(1000000);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}