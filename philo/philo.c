/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:23:41 by idouni            #+#    #+#             */
/*   Updated: 2023/02/10 12:23:59 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	NULL1()
{
	printf("thread uno\n");
	printf("bye uno\n\n");
	pthread_exit(NULL);
}

void	NULL2()
{
	printf("thread dos\n");
	printf("bye dos\n\n");
	pthread_exit(NULL);
}

void	NULL3()
{
	printf("hread trs\n");
	printf("bye trs\n\n");
	pthread_exit(NULL);
}

int	main()
{
	pthread_t	thread;
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread, NULL, (void *)NULL1, NULL);
	pthread_create(&thread1, NULL, (void *)NULL2, NULL);
	pthread_create(&thread2, NULL, (void *)NULL3, NULL);

	pthread_join(thread, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_exit(NULL);

	return (0);
}
