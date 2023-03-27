/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:39:36 by idouni            #+#    #+#             */
/*   Updated: 2023/03/11 17:39:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_mutexes2(t_data data, t_params params, pthread_mutex_t	*mutexes)
{
	int	i;

	i = 0;
	(void)data;
	while (i < params.n_of_philos)
	{
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (MUTEXES);
		usleep(200);
		i++;
	}
	return (0);
}

t_info	info_init(t_params params, t_data data, t_info info)
{
	info.ph = NULL;
	info.mt = NULL;
	info.n = NULL;
	info.ph = h_malloc(data, sizeof(pthread_t) * \
	(params.n_of_philos + 1), info.ph);
	info.mt = h_malloc(data, sizeof(pthread_mutex_t) * \
	(params.n_of_philos + 1), info.ph);
	init_mutexes2(data, params, info.mt);
	return (info);
}

t_list	node_init(t_params params, int i, t_info info)
{
	info.n->philosopher_id = i + 1;
	info.n->l_fork = &info.mt[i];
	info.n->r_fork = &info.mt[(i + 1) % params.n_of_philos];
	info.n->time_to_think = params.t_to_think;
	info.n->time_to_sleep = params.t_to_sleep;
	info.n->time_to_eat = params.t_to_eat;
	info.n->num_of_meals = params.n_of_meals;
	info.n->eaten_meals = 0;
	info.n->state = ALIVE;
	info.n->think_state =  ALREADY_THINKING;
	return (*info.n);
}

int	create_philos(t_params params, t_data *data)
{
	t_info			info;
	int				i;
	static t_locks	lock;

	info.ph = NULL;
	info = info_init(params, *data, info);
	i = 0;
	while (i < params.n_of_philos)
	{
		info.n = ft_lstnew(*data);
		ft_lstadd_back(&data->head, info.n);
		*(info.n) = node_init(params, i, info);
		info.n->philosopher = info.ph[i];
		usleep(200);
		info.n->lock = &lock;
		if (i == params.n_of_philos - 1)
			info.n->next = data->head;
		else
			info.n = info.n->next;
		i++;
	}
	data->head = info.n;
	data->mutexes = info.mt;
	data->threads = info.ph;
	return (0);
}

int	join_threads(t_data *data, t_params params)
{
	int		i;
	t_list	*n;

	ft_time();
	i = 0;
	n = data->head;
	printf("===SUMULATION_STARTS============\n");
	while (n && i < params.n_of_philos)
	{
		n->time_left = n->time_to_think;
		if (pthread_create(&n->philosopher, NULL, philosopher_state, n))
			return (THREADS);
		usleep(200);
		if (pthread_detach(n->philosopher))
			return (THREADS);
		usleep(200);
		n = n->next;
		i++;
	}
	return (0);
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
	usleep(100);
	if (pthread_mutex_init(&n->lock->lock2, NULL))
		return (MUTEXES);
	usleep(100);
	if (pthread_mutex_init(&n->lock->lock3, NULL))
		return (MUTEXES);
	usleep(100);
	if (pthread_mutex_init(&n->lock->lock4, NULL))
		return (MUTEXES);
	usleep(100);
	if (pthread_mutex_init(&n->lock->lock5, NULL))
		return (MUTEXES);
	usleep(100);
	return (0);
}
