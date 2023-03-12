// #include "philo.h"

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void	*NULL1(void *arg)
// {
// 	int	n = 0;

// 	// printf("%lu\n", mutex);
// 	pthread_mutex_init(&mutex, NULL);
// 	pthread_mutex_lock(&mutex);
// 	{
// 		n = 15;
// 		usleep(9000);
// 	}
// 	pthread_mutex_unlock(&mutex);
// 	return ((void *)n);
// }

// int	main()
// {
// 	int	n = 0;
// 	int	n2 = 0;
// 	int	n3 = 0;
// 	pthread_t	thread1;
// 	pthread_t	thread2;
// 	pthread_t	thread3;
// 	// int	i;

// 	// i = 0;

// 	// int		p1 = 1;
// 	// int		p2 = 2;
// 	// int		p3 = 3;
// 	// pthread_mutex_t mutex;
// 	pthread_create(&thread1, NULL, (void *)NULL1, NULL);
// 	pthread_create(&thread2, NULL, (void *)NULL1, NULL);
// 	pthread_create(&thread3, NULL, (void *)NULL1, NULL);
// 	// printf("%lu\n", mutex);
// 	// printf("%lu lock\n", l);
// 	// printf("%lu unlock\n\n",u);

// 	// printf("%lu\n", mutex);
// 	// printf("%lu lock\n", l);
// 	// printf("%lu unlock\n\n",u);
// 	// time_t	p;
// 	// time_t	p1;
// 	// struct timezone tzp;
// 	// struct timeval tp;
// 	// pthread_create(&thread3, NULL, (void *)NULL3, &p3);
// 	// pthread_detach(thread1);
// 	// pthread_detach(thread2);
// 	// pthread_detach(thread3);

// 	pthread_join(thread3, (void *) &n3);
// 	pthread_join(thread2, (void *) &n2);
// 	pthread_join(thread1, (void *) &n);
// 	// pthread_join(thread3, NULL);
// 	//pthread_join(thread[i], NULL);

// 	// while(1);
// 	// printf("%lu\n", thread);
// 	// sleep(2);
// 	// gettimeofday(&tp, &tzp);
// 	// p = tp.tv_sec;
// 	// printf("%lu\n", p);
// 	// sleep(2);
// 	// gettimeofday(&tp, &tzp);
// 	// p1 = tp.tv_sec - p;
// 	// printf("%lu\n", p1);
// 	// sleep(2);
// 	// gettimeofday(&tp, &tzp);
// 	// p1 = tp.tv_sec - p;
// 	// printf("%lu\n", p1);
// 	// sleep(2);
// 	// gettimeofday(&tp, &tzp);
// 	// p1 = tp.tv_sec - p;
// 	printf("from first thread  : %d\n", n);
// 	printf("from second thread ; %d\n", n2);
// 	printf("from third thread  ; %d\n", n3);
// 	return (0);
// }

// #include <stdio.h>
// #include <pthread.h>

// void *my_thread_function(void *arg) {
//     int result = 42;
//     return ((void*) result); // exit thread and return 42
// }

// int main() {
//     pthread_t my_thread;
//     int thread_result;

//     pthread_create(&my_thread, NULL, my_thread_function, NULL);
//     pthread_join(my_thread, &thread_result); // join thread and retrieve result
//     printf("Thread result: %d\n", thread_result);

//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// pthread_mutex_t mutex;
// pthread_cond_t cond;
// int data_ready = 0;

// void* my_function(void* arg) {
//     pthread_mutex_lock(&mutex);
//     while (!data_ready) {
//         pthread_cond_wait(&cond, &mutex);
//     }
//     // do some work now that data is ready
//     pthread_mutex_unlock(&mutex);
//     return NULL;
// }

// void signal_data_ready() {
//     pthread_mutex_lock(&mutex);
//     data_ready = 1;
//     pthread_cond_signal(&cond);
//     pthread_mutex_unlock(&mutex);
// }

// int main() {
//     pthread_t thread;
//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);
//     pthread_create(&thread, NULL, my_function, NULL);

//     // do some work
//     sleep(5);

//     signal_data_ready();

//     pthread_join(thread, NULL);
//     pthread_mutex_destroy(&mutex);
//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// pthread_mutex_t mutex;

// void* my_function(void* arg) {
//     pthread_mutex_init(&mutex, NULL);
//     while (1) {
//     	pthread_mutex_lock(&mutex);
// 		printf("the thread\n");
// 		printf("sleep 2\n");
//         sleep(2); // sleep for 1 second
//         pthread_mutex_unlock(&mutex);
//     }
// }

// void signal_unlock() {
//     pthread_mutex_unlock(&mutex);
// }

// void signal_lock() {
//     pthread_mutex_lock(&mutex);
// }

// int main() {
//     pthread_t thread;
// 	printf("===SUMULATION_START===========\n");
// 	// pthread_mutex_lock(&mutex);
//     pthread_create(&thread, NULL, my_function, NULL);
// 	while (1)
// 	{
// 		signal_lock();
// 		pthread_mutex_lock(&mutex);
// 		printf("sleep 5\n");
// 		sleep(2);
// 		signal_unlock();
// 	}
// 	pthread_detach(thread);

//     pthread_mutex_destroy(&mutex);
// 	printf("===SUMULATION_ENDS===========\n");
//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/time.h>

// #define NUM_PHILOSOPHERS 900
// #define NUM_CHOPSTICKS 5
// #define MAX_WAIT_TIME 500000

// long long ft_time()
// {
//     static long long init_time;
//     struct timeval    tp;
//     long long   t;

//     gettimeofday(&tp, NULL);
//     if (!init_time)
//         init_time = (long long)tp.tv_usec + ((long long)tp.tv_sec * 10000);
//     t = (((long long)tp.tv_usec + (long long)tp.tv_sec * 10000) - init_time) / 1000;
//     return (t);
// }

// pthread_mutex_t chopstick_mutex[NUM_CHOPSTICKS];
// pthread_t philosophers[NUM_PHILOSOPHERS];

// void *philosopher(void *arg) {
//     int id = *(int *)arg;
//     int left_chopstick = id;
//     int right_chopstick = (id + 1) % NUM_CHOPSTICKS;
//     int wait_time;

//     while (1) {
//         printf("%lldms Philosopher %d is thinking\n", ft_time() ,id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         usleep(wait_time);

//         printf("%lldms Philosopher %d is hungry\n", ft_time() ,id);

//         pthread_mutex_lock(&chopstick_mutex[left_chopstick]);
//         printf("%lldms Philosopher %d picked up chopstick %d\n", ft_time() ,id, left_chopstick);

//         pthread_mutex_lock(&chopstick_mutex[right_chopstick]);
//         printf("%lldms Philosopher %d picked up chopstick %d\n", ft_time() ,id, right_chopstick);

//         printf("%lldms Philosopher %d is eating\n", ft_time() ,id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         usleep(wait_time);

//         pthread_mutex_unlock(&chopstick_mutex[right_chopstick]);
//         printf("%lldms Philosopher %d put down chopstick %d\n", ft_time() ,id, right_chopstick);

//         pthread_mutex_unlock(&chopstick_mutex[left_chopstick]);
//         printf("%lldms Philosopher %d put down chopstick %d\n", ft_time() ,id, left_chopstick);
//     }
// }

// int main() {
//     int i, ids[NUM_PHILOSOPHERS];

//     srand(time(NULL));

//     for (i = 0; i < NUM_CHOPSTICKS; i++) {
//         pthread_mutex_init(&chopstick_mutex[i], NULL);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         ids[i] = i;
//         pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         pthread_join(philosophers[i], NULL);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/time.h>

// #define NUM_PHILOSOPHERS 5
// #define NUM_CHOPSTICKS 5
// #define MAX_WAIT_TIME 500000

// pthread_mutex_t chopstick_mutex[NUM_CHOPSTICKS];
// pthread_t philosophers[NUM_PHILOSOPHERS];

// void *philosopher(void *arg) {
//     int id = *(int *)arg;
//     int left_chopstick = id;
//     int right_chopstick = (id + 1) % NUM_CHOPSTICKS;
//     int wait_time;

//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     long long start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

//     while (1) {
//         printf("[%lldms] Philosopher %d is thinking\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         usleep(wait_time);

//         printf("[%lldms] Philosopher %d is hungry\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id);

//         pthread_mutex_lock(&chopstick_mutex[left_chopstick]);
//         printf("[%lldms] Philosopher %d picked up chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id, left_chopstick);

//         pthread_mutex_lock(&chopstick_mutex[right_chopstick]);
//         printf("[%lldms] Philosopher %d picked up chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id, right_chopstick);

//         printf("[%lldms] Philosopher %d is eating\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         usleep(wait_time);

//         pthread_mutex_unlock(&chopstick_mutex[right_chopstick]);
//         printf("[%lldms] Philosopher %d put down chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id, right_chopstick);

//         pthread_mutex_unlock(&chopstick_mutex[left_chopstick]);
//         printf("[%lldms] Philosopher %d put down chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time, id, left_chopstick);
//     }
// }

// int main() {
//     int i, ids[NUM_PHILOSOPHERS];

//     srand(time(NULL));

//     for (i = 0; i < NUM_CHOPSTICKS; i++) {
//         pthread_mutex_init(&chopstick_mutex[i], NULL);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         ids[i] = i;
//         pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         pthread_join(philosophers[i], NULL);
//     }

//     return 0;
// }

// 

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/time.h>

// #define NUM_PHILOSOPHERS 5
// #define NUM_CHOPSTICKS 5
// #define MAX_WAIT_TIME 500000

// struct Philosopher {
//     pthread_mutex_t* left_chopstick;
//     pthread_mutex_t* right_chopstick;
//     int id;
//     long long start_time;
// };

// pthread_mutex_t chopstick_mutex[NUM_CHOPSTICKS];
// pthread_t philosophers[NUM_PHILOSOPHERS];

// void *philosopher(void *arg) {
//     struct Philosopher* philosopher = (struct Philosopher*) arg;
//     int wait_time;

//     while (1) {
//         struct timeval tv;
//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d is thinking\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         printf("\n\nwait_time is %d\n\n", wait_time);
//         usleep(wait_time);

//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d is hungry\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id);

//         pthread_mutex_lock(philosopher->left_chopstick);
//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d picked up chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id, philosopher->id);

//         pthread_mutex_lock(philosopher->right_chopstick);
//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d picked up chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id, (philosopher->id + 1) % NUM_CHOPSTICKS);

//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d is eating\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id);

//         wait_time = rand() % MAX_WAIT_TIME;
//         usleep(wait_time);

//         pthread_mutex_unlock(philosopher->right_chopstick);
//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d put down chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id, (philosopher->id + 1) % NUM_CHOPSTICKS);

//         pthread_mutex_unlock(philosopher->left_chopstick);
//         gettimeofday(&tv, NULL);
//         printf("[%lldms] Philosopher %d put down chopstick %d\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philosopher->start_time, philosopher->id, philosopher->id);
//     }
// }

// int main() {
//     int i, ids[NUM_PHILOSOPHERS];
//     pthread_mutex_t chopstick_mutex[NUM_CHOPSTICKS];
//     pthread_t philosophers[NUM_PHILOSOPHERS];

//     srand(time(NULL));

//     for (i = 0; i < NUM_CHOPSTICKS; i++) {
//         pthread_mutex_init(&chopstick_mutex[i], NULL);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         ids[i] = i;
//         pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
//     }

//     for (i = 0; i < NUM_PHILOSOPHERS; i++) {
//         pthread_join(philosophers[i], NULL);
//     }

//     return 0;
// }


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

pthread_t   thread;
pthread_mutex_t mutex;

void    *function(void *arg)
{
    static int p = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
        p = 42;
    pthread_mutex_unlock(&mutex);
    return((void *)p);
}

int main()
{
    int res = 0;

    pthread_mutex_lock(&mutex);
    pthread_create(&thread, NULL, function, NULL);
    pthread_mutex_lock(&mutex);

    pthread_join(thread, &res);

    printf("%d\n", res);
}