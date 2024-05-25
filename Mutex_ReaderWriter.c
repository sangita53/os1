#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t reads_mutex, writes_mutex, resource_mutex;
int data = 0;
int reader_count = 0;

void *reader(void *arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++) 
    {
        pthread_mutex_lock(&reads_mutex);
        reader_count++;
        if (reader_count == 1) {
            pthread_mutex_lock(&resource_mutex);
        }
        pthread_mutex_unlock(&reads_mutex);

        printf("Reader %d reads data: %d\n", id, data);

        pthread_mutex_lock(&reads_mutex);
        reader_count--;
        if (reader_count == 0) {
            pthread_mutex_unlock(&resource_mutex);
        }
        pthread_mutex_unlock(&reads_mutex);

        usleep(1000000);
    }
}

void *writer(void *arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&writes_mutex);

        data++;
        printf("Writer %d writes data: %d\n", id, data);

        pthread_mutex_unlock(&writes_mutex);

        usleep(2000000);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    pthread_mutex_init(&reads_mutex, NULL);
    pthread_mutex_init(&writes_mutex, NULL);
    pthread_mutex_init(&resource_mutex, NULL);

    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&reads_mutex);
    pthread_mutex_destroy(&writes_mutex);
    pthread_mutex_destroy(&resource_mutex);

    return 0;
}