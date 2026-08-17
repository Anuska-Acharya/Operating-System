#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopstick[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    // Allow only N-1 philosophers to try eating
    sem_wait(&room);

    // Pick up left chopstick
    pthread_mutex_lock(&chopstick[id]);

    // Pick up right chopstick
    pthread_mutex_lock(&chopstick[(id + 1) % N]);

    printf("Philosopher %d is eating\n", id);
    sleep(2);

    // Put down right chopstick
    pthread_mutex_unlock(&chopstick[(id + 1) % N]);

    // Put down left chopstick
    pthread_mutex_unlock(&chopstick[id]);

    printf("Philosopher %d finished eating\n", id);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t philosophers[N];
    int id[N];

    // Initialize chopsticks
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Initialize semaphore
    sem_init(&room, 0, N - 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    // Wait for all philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&chopstick[i]);
    }

    sem_destroy(&room);

    return 0;
}