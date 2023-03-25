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

t_info	info_init(t_params params, t_data data, t_info info)
{
	info.ph = NULL;
	info.mt = NULL;
	info.n = NULL;
	info.ph = h_malloc(data, sizeof(pthread_t) * \
	(params.n_of_philos + 1), info.ph);
	info.mt = h_malloc(data, sizeof(pthread_mutex_t) * \
	(params.n_of_philos + 1), info.ph);
	data.head = info.n;
	data.mutexes = info.mt;
	data.threads = info.ph;
	return (info);
}

t_list	node_init(t_params params, int i, t_info info)
{
	info.n->philosopher_id = i + 1;
	info.n->fork = info.mt[i];
	info.n->time_to_think = params.t_to_think;
	info.n->time_to_sleep = params.t_to_sleep;
	info.n->time_to_eat = params.t_to_eat;
	info.n->num_of_meals = params.n_of_meals;
	info.n->eaten_meals = 0;	
	info.n->lock_status = UNLOCKED;
	info.n->old_status =  ALREADY_THINKING;
	return (*info.n);
}

t_data	create_philos(t_params params, t_data data)
{
	t_info			info;
	int				i;
	static t_locks	lock;

	info.ph = NULL;
	info = info_init(params, data, info);
	i = 0;
	while (i < params.n_of_philos)
	{
		info.n = ft_lstnew(data);
		ft_lstadd_back(&data.head, info.n);
		*(info.n) = node_init(params, i, info);
		info.n->philosopher = info.ph[i];
		usleep(200);
		info.n->lock = &lock;
		if (i == params.n_of_philos - 1)
			info.n->next = data.head;
		else
			info.n = info.n->next;
		i++;
	}
	return (data);
}

t_data	join_threads(t_data data, t_params params)
{
	int		i;
	t_list	*n;

	ft_time();
	i = 0;
	n = data.head;
	while (n && i < params.n_of_philos)
	{
		n->l_fork = &n->fork;
		n->r_fork = &n->next->fork;
		n->time_left = n->time_to_think;
		if (pthread_create(&n->philosopher, NULL, philosopher_state, n))
			ft_exit_with_error(THREADS, data);
		usleep(200);
		if (pthread_detach(n->philosopher))
			ft_exit_with_error(THREADS, data);
		usleep(200);
		n = n->next;
		i++;
	}
	return (data);
}

t_data	init_mutexes(t_data data, t_params params)
{
	int		i;
	t_list	*n;

	i = 0;
	n = data.head;
	if (pthread_mutex_init(&n->lock->lock1, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&n->lock->lock2, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&n->lock->lock3, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&n->lock->lock4, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&n->lock->lock5, NULL))
		ft_exit_with_error(MUTEXES, data);
	usleep(200);
	while (i < params.n_of_philos)
	{
		if (pthread_mutex_init(&n->fork, NULL))
			ft_exit_with_error(MUTEXES, data);
		usleep(200);
		i++;
		n = n->next;
	}
	return (data);
}
