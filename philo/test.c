#include "philo.h"

	pthread_t	thread;
	pthread_t	thread1;
	pthread_t	thread2;

void	*NULL1()
{
	printf("thread uno\n");
	printf("bye uno\n\n");
    return (0);
}

void	*NULL2()
{
	printf("thread dos\n");
	printf("bye dos\n\n");
	pthread_join(thread, NULL);
    return (0);
}

void	*NULL3()
{
	printf("hread trs\n");
	printf("bye trs\n\n");
	pthread_join(thread1, NULL);
    return (0);
}

int	main()
{

	pthread_create(&thread, NULL, (void *)NULL1, NULL);
	pthread_create(&thread1, NULL, (void *)NULL2, NULL);
	pthread_create(&thread2, NULL, (void *)NULL3, NULL);

	pthread_join(thread2, NULL);

	// pthread_exit(NULL);

	return (0);
}