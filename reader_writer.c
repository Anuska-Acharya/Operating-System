#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;
int reader_count = 0;

pthread_mutex_t mutex;
sem_t wrt;

// Reader
void *reader(void *arg)
{
    int id = *(int *)arg;

    // Increase reader count
    pthread_mutex_lock(&mutex);
    reader_count++;

    if (reader_count == 1)
        sem_wait(&wrt);   // First reader blocks writers

    pthread_mutex_unlock(&mutex);

    // Reading
    printf("Reader %d is reading data = %d\n", id, data);
    sleep(1);

    // Decrease reader count
    pthread_mutex_lock(&mutex);
    reader_count--;

    if (reader_count == 0)
        sem_post(&wrt);   // Last reader allows writers

    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer
void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&wrt);       // Writer gets exclusive access

    data++;
    printf("Writer %d is writing data = %d\n", id, data);
    sleep(1);

    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t readers[3], writers[2];

    int reader_id[3] = {1, 2, 3};
    int writer_id[2] = {1, 2};

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }

    // Wait for readers
    for (int i = 0; i < 3; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Wait for writers
    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Destroy synchronization objects
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}