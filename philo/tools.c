/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:36:47 by idouni            #+#    #+#             */
/*   Updated: 2023/02/10 12:37:03 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse(t_data data, t_params *params, int argc, char **argv)
{
	(void)argv;
	(void)data;
	if (argc < 5 || argc > 6)
		return (ARGS);
	params->n_of_philos = ft_atoi(argv[1]);
	if (params->n_of_philos == -1)
		return (ARGS);
	params->t_to_think = ft_atoi(argv[2]);
	if (params->t_to_think == -1)
		return (ARGS);
	params->t_to_eat = ft_atoi(argv[3]);
	if (params->t_to_eat == -1)
		return (ARGS);
	params->t_to_sleep = ft_atoi(argv[4]);
	if (params->t_to_sleep == -1)
		return (ARGS);
	if (argc == 5)
		params->n_of_meals = -1;
	else
	{
		params->n_of_meals = ft_atoi(argv[5]);
		if (params->n_of_meals == -1)
			return (ARGS);
	}
	return (0);
}

void	destroy_mutexes(t_data data)
{
	t_list	*n;
	int		i;

	i = 0;
	n = data.head;
	while (n && i < data.params.n_of_philos)
	{
		pthread_mutex_destroy(&data.mutexes[i]);
		n = n->next;
		i++;
	}
}

void	ft_exit_with_error(int n, t_data data)
{
	if (data.mutexes)
	{
		destroy_mutexes(data);
		free(data.mutexes);
	}
	if (data.threads)
		free(data.threads);
	if (data.head)
		ft_lstclear(&data.head, data.params.n_of_philos);
	printf("\n\x1B[32m");
	if (n == ARGS)
	{
		printf("===HINT=========================\n");
		printf("Program need at least 4 arguments specefied like this:\n");
		printf("Number_of_philos Time_to_die time_to_eat Time_to_sleep ");
		printf("Number_of_meals(opptional)\n\n");
	}
	else if (n == MALLOC)
		printf("ERROR : No enough memory to be allocated\n\n");
	else if (n == MUTEXES)
		printf("ERROR : Mutexe didn't created properly\n\n");
	else if (n == THREADS)
		printf("ERROR : Thread didn't created properly\n\n");
}

time_t	ft_time(void)
{
	static time_t	init_time;
	struct timeval	tp;
	time_t			t;

	gettimeofday(&tp, NULL);
	if (!init_time)
	{
		init_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
	}
	t = (((time_t)(tp.tv_usec / 1000) + (time_t)tp.tv_sec * 1000) - init_time);
	return (t);
}

int	init_mutexes(t_data *data, t_params params)
{
	int		i;
	t_list	*n;

	(void)params;
	i = 0;
	n = data->head;
	if (pthread_mutex_init(&n->lock->lock1, NULL))
		return (MUTEXES);
	if (pthread_mutex_init(&n->lock->lock2, NULL))
		return (MUTEXES);
	if (pthread_mutex_init(&n->lock->lock3, NULL))
		return (MUTEXES);
	return (0);
}


void	ft_usleep(time_t time)
{
	static time_t	ref;
	time_t			d_time;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	if (!ref)
		ref = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
	d_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000) - ref;

	usleep((time - 10) * 1000);
	while (d_time < time)
	{
		gettimeofday(&tp, NULL);
		d_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
	}
}
