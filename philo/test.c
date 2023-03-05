#include "philo.h"

// 	pthread_t	thread;

// 	int	p = 0;

// void	*NULL1()
// {
// 	printf("create thread number\n");
// 	p++;
// 	printf(" ##%d\n\n", p);
// 	// pthread_exit(NULL);
// 	// while (1);
//     return (0);
// }

int	main()
{
	// pthread_t	thread;
	// int	i;

	// i = 0;

	time_t	p;
	time_t	p1;
	struct timezone tzp;
	struct timeval tp;

	// pthread_create(&thread, NULL, (void *)NULL1, NULL);
	// // printf("%lu\n", thread);
	// pthread_join(thread, NULL);
	// printf("%lu\n", thread);
	// sleep(2);
	gettimeofday(&tp, &tzp);
	p = tp.tv_sec;
	printf("%lu\n", p);
	sleep(2);
	gettimeofday(&tp, &tzp);
	p1 = tp.tv_sec - p;
	printf("%lu\n", p1);
	sleep(2);
	gettimeofday(&tp, &tzp);
	p1 = tp.tv_sec - p;
	printf("%lu\n", p1);
	sleep(2);
	gettimeofday(&tp, &tzp);
	p1 = tp.tv_sec - p;
	printf("%lu\n", p1);
	return (0);
}