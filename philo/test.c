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

// // #include <stdio.h>
// // #include <pthread.h>

// // void *my_thread_function(void *arg) {
// //     int result = 42;
// //     return ((void*) result); // exit thread and return 42
// // }

// // int main() {
// //     pthread_t my_thread;
// //     int thread_result;

// //     pthread_create(&my_thread, NULL, my_thread_function, NULL);
// //     pthread_join(my_thread, &thread_result); // join thread and retrieve result
// //     printf("Thread result: %d\n", thread_result);

// //     return 0;
// // }

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

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* my_function(void* arg) {
    while (1) {
    	pthread_mutex_lock(&mutex);
		printf("the thread\n");
        pthread_mutex_unlock(&mutex);
		printf("sleep 2\n");
        sleep(2); // sleep for 1 second
        pthread_mutex_lock(&mutex);
    	pthread_mutex_unlock(&mutex);
    }
}

void signal_data_ready() {
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t thread;
	printf("===SUMULATION_START===========\n");
    pthread_mutex_init(&mutex, NULL);
    // pthread_mutex_lock(&mutex);
    pthread_create(&thread, NULL, my_function, NULL);
    pthread_detach(thread);

    // do some work
	printf("sleep 5\n");
    sleep(5);

    signal_data_ready();

	while (1);
    pthread_mutex_destroy(&mutex);
	printf("===SUMULATION_ENDS===========\n");
    return 0;
}