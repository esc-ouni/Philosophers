#include "philo.h"

	// pthread_t	thread;

	int	p = 0;

// void	*NULL1(void *arg)
// {
// 	printf("create thread number\n");
// 	p++;
// 	while (1)
// 	{
// 		printf(" ##%d\n\n", p);
// 		sleep(1);
// 	}
// 	// pthread_exit(NULL);
// 	// while (1)
// 	// {
// 	// 	printf("hello\n");
// 	// 	continue;
// 	// }
//     // return (0);
// }

// void	*NULL2(void *arg)
// {
// 	printf("create thread number\n");
// 	p++;
// 	while (1)
// 	{
// 		printf(" ##%d\n\n", p);
// 		sleep(1);
// 	}
// 	// pthread_exit(NULL);
// 	// while (1)
// 	// {
// 	// 	printf("hello\n");
// 	// 	continue;
// 	// }
//     // return (0);
// }

void	*NULL1(void *arg)
{
	int	p = *(int *)arg;
	while (1)
	{
		printf("hello from ##%d\n", p);
		sleep(1);
	}

}

void	*NULL2(void *arg)
{
	int	p = *(int *)arg;
	while (1)
	{
		printf("hello from ##%d\n", p);
		sleep(1);
	}

}

void	*NULL3(void *arg)
{
	int	p = *(int *)arg;
	while (1)
	{
		printf("hello from ##%d\n", p);
		sleep(1);
	}

}

// void	*NULL2(void *arg)
// {
// 	int	p = *(int *)arg;
// 	printf("hello from ##%d\n", p);

// }

// void	*NULL3(void *arg)
// {
// 	int	p = *(int *)arg;
// 	printf("hello from ##%d\n", p);

// }

int	main()
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	int	i;

	i = 0;

	int		p1 = 1;
	int		p2 = 2;
	int		p3 = 3;
	// pthread_mutex_t mutex;
	// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	// pthread_mutex_init(&mutex, NULL);
	// printf("%lu\n", mutex);
	// pthread_mutex_lock(&mutex);
	// printf("%lu\n", mutex);
	// pthread_mutex_unlock(&mutex);
	// time_t	p;
	// time_t	p1;
	// struct timezone tzp;
	// struct timeval tp;
	pthread_create(&thread1, NULL, (void *)NULL1, &p1);
	pthread_create(&thread2, NULL, (void *)NULL2, &p2);
	pthread_create(&thread3, NULL, (void *)NULL3, &p3);
	pthread_detach(thread1);
	pthread_detach(thread2);
	pthread_detach(thread3);
	//pthread_join(thread[i], NULL);

	while(1);
	// printf("%lu\n", thread);
	// sleep(2);
	// gettimeofday(&tp, &tzp);
	// p = tp.tv_sec;
	// printf("%lu\n", p);
	// sleep(2);
	// gettimeofday(&tp, &tzp);
	// p1 = tp.tv_sec - p;
	// printf("%lu\n", p1);
	// sleep(2);
	// gettimeofday(&tp, &tzp);
	// p1 = tp.tv_sec - p;
	// printf("%lu\n", p1);
	// sleep(2);
	// gettimeofday(&tp, &tzp);
	// p1 = tp.tv_sec - p;
	// printf("%lu\n", mutex);
	return (0);
}