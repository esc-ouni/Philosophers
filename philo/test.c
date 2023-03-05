#include "philo.h"

	pthread_t	thread;

	int	p = 0;

void	*NULL1()
{
	printf("create thread number\n");
	p++;
	printf(" ##%d\n\n", p);
	while (1);
    return (0);
}

int	main()
{
	pthread_t	thread[1000000];
	int	i;

	i = 0;

while (i <= 10241)
{
	pthread_create(&thread[i], NULL, (void *)NULL1, NULL);
	// pthread_join(thread[i], NULL);
	i++;
}

	// pthread_exit(NULL);

	return (0);
}