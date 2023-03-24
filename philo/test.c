#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_PHILOSOPHERS 100

pthread_mutex_t putex;

int num_philosophers;
int time_to_die;
int time_to_eat;
int time_to_sleep;
int num_times_each_philosopher_must_eat = -1;

pthread_mutex_t forks[MAX_PHILOSOPHERS];
pthread_t philosophers[MAX_PHILOSOPHERS];
int philosopher_ids[MAX_PHILOSOPHERS];

int meals_eaten[MAX_PHILOSOPHERS];
int total_meals_eaten = 0;

int timestamp()
{
    struct timeval tv;
    static int init_time;

    gettimeofday(&tv, NULL);
    if (!init_time)
	{
		init_time = tv.tv_sec * 1000 + tv.tv_usec / 1000 ;
	}
    return tv.tv_sec * 1000 + tv.tv_usec / 1000 - init_time;
}

void log_event(char *event, int id)
{
    pthread_mutex_lock(&putex);
    printf("%d %d %s\n", timestamp(), id + 1, event);
    pthread_mutex_unlock(&putex);
}

void *philosopher(void *arg)
{
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;

    while (1) {
        // Thinking
        log_event("is thinking", id);
        usleep(1000000);

        // Waiting for forks
        log_event("has taken a fork", id);
        pthread_mutex_lock(&forks[left_fork]);
        log_event("has taken a fork", id);
        pthread_mutex_lock(&forks[right_fork]);

        // Eating
        log_event("is eating", id);
        meals_eaten[id]++;
        // total_meals_eaten++;
        usleep(time_to_eat * 1000);

        // Releasing forks
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);

        // Sleeping
        log_event("is sleeping", id);
        usleep(time_to_sleep * 1000);

        // Checking if philosopher has died
        if (time_to_die != 0 && meals_eaten[id] == 0 &&
            timestamp() >= time_to_die) {
            log_event("died", id);
            pthread_exit(NULL);
        }

        // Checking if all philosophers have eaten enough
        if (num_times_each_philosopher_must_eat != -1 &&
            total_meals_eaten >= num_philosophers * num_times_each_philosopher_must_eat) {
            pthread_exit(NULL);
        }
    }
}

int main(int argc, char **argv)
{
    // Parse command line arguments
    if (argc < 5) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
    num_philosophers = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    if (argc == 6) {
        num_times_each_philosopher_must_eat = atoi(argv[5]);
    }

    pthread_mutex_init(&putex, NULL);
    // Initialize mutexes for forks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create threads for philosophers
    for (int i = 0; i < num_philosophers; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for all philosopher threads to finish
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
