#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_READERS 3
#define NUM_WRITERS 2
sem_t reads, writes, resource;
int data = 0;
int reader_count = 0;
void *reader(void *arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&reads);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&resource);
        }
        sem_post(&reads);
        printf("Reader %d reads data: %d\n", id, data);
        sem_wait(&reads);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource);
        }
        sem_post(&reads);
        usleep(1000000);
    }
}
void *writer(void *arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&writes);
        data++;
        printf("Writer %d writes data: %d\n", id, data);
        sem_post(&writes);
        usleep(2000000);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    sem_init(&reads, 0, 1);
    sem_init(&writes, 0, 1);
    sem_init(&resource, 0, 1);
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
    sem_destroy(&reads);
    sem_destroy(&writes);
    sem_destroy(&resource);
    return 0;
}





// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// #define NUM_READERS 3
// #define NUM_WRITERS 2

// sem_t reads, writes, resource;
// int data = 0;
// int reader_count = 0;

// void *reader(void *arg) {
//     int id =*((int*)arg);
//     for (int i = 0; i < 10; i++)
//      {
//         sem_wait(&reads);
//         reader_count++;
//         if (reader_count == 1) {
//             sem_wait(&resource);
//         }
//         sem_post(&reads);

//         printf("Reader %d reads data: %d\n", id, data);

//         sem_wait(&reads);
//         reader_count--;
//         if (reader_count == 0) {
//             sem_post(&resource);
//         }
//         sem_post(&reads);

//         usleep(1000000);
//     }
// }

// void *writer(void *arg) {
//     int id = *((int*)arg);
//     for (int i = 0; i < 10; i++)
//      {
//         sem_wait(&writes);

//         data++;
//         printf("Writer %d writes data: %d\n", id, data);

//         sem_post(&writes);

//         usleep(2000000);
//     }
// }

// int main() {
//     pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
//     int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

//     sem_init(&reads, 0, 1);
//     sem_init(&writes, 0, 1);
//     sem_init(&resource, 0, 1);

//     for (int i = 0; i < NUM_READERS; ++i) {
//         reader_ids[i] = i;
//         pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
//     }

//     for (int i = 0; i < NUM_WRITERS; ++i) {
//         writer_ids[i] = i;
//         pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
//     }

//     for (int i = 0; i < NUM_READERS; ++i) {
//         pthread_join(readers[i], NULL);
//     }

//     for (int i = 0; i < NUM_WRITERS; ++i) {
//         pthread_join(writers[i], NULL);
//     }

//     sem_destroy(&reads);
//     sem_destroy(&writes);
//     sem_destroy(&resource);

//     return 0;
// }