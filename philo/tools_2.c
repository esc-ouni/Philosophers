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
	(params.n_of_philos + 300), info.ph);
	info.mt = h_malloc(data, sizeof(pthread_mutex_t) * \
	(params.n_of_philos + 300), info.ph);
	data.head = info.n;
	data.mutexes = info.mt;
	data.threads = info.ph;
	return (info);
}

t_list	node_init(t_params params, int i, t_info info)
{
	info.n->philosopher_id = i + 1;
	info.n->l_fork = info.mt[i];
	info.n->time_to_think = params.t_to_think;
	info.n->time_to_sleep = params.t_to_sleep;
	info.n->time_to_eat = params.t_to_eat;
	info.n->num_of_meals = params.n_of_meals;
	info.n->lock_status = UNLOCKED;
	info.n->old_status = THINKING_STATE;
	return (*info.n);
}

t_data	create_philos(t_params params, t_data data)
{
	t_info			info;
	int				i;

	info.ph = NULL;
	info = info_init(params, data, info);
	i = 0;
	while (i < params.n_of_philos)
	{
		info.n = ft_lstnew(data);
		ft_lstadd_back(data, &data.head, info.n);
		*(info.n) = node_init(params, i, info);
		if (pthread_create(&info.ph[i], NULL, philosopher_state, info.n))
			ft_exit_with_error(THREADS, data);
		info.n->philosopher = info.ph[i];
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
		if (pthread_detach(n->philosopher))
			ft_exit_with_error(THREADS, data);
		n = n->next;
		i++;
	}
	return (data);
}

void	*philosopher_state(void *arg)
{
	pthread_mutex_lock(&klop2);
	int				max;
	int				id;
	t_list			*node;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	// printf("\n%p\n%p\n%p\n%p\n\n", max, id, node, l_fork, r_fork);

	max = 0;
	ft_time();
	node = (t_list  *)arg;
	pthread_mutex_lock(&klop4);
	pthread_mutex_lock(&klop3);
	l_fork = &node->l_fork;
	pthread_mutex_unlock(&klop3);
	r_fork = &node->next->l_fork;
	pthread_mutex_unlock(&klop4);
	id = node->philosopher_id;
	node->eaten_meals = 0;
	node->time_left = node->time_to_think;
	// node->num_of_meals = 0;
	// printf("\n\n%lld\n\n", node->num_of_meals);
	while (1)
	{
		// pthread_mutex_lock(&klop5);
		if (node->eaten_meals == node->num_of_meals)
		{
			node->eat_state = EAT_ENOUGH;
			break ;
		}
		check_death(node, ft_time());
		if (node->old_status == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->old_status = ALREADY_THINKING;
		}
		check_death(node, ft_time());
		if (node->lock_status == UNLOCKED && \
		node->next->lock_status == UNLOCKED && node->eaten_meals <= max)
		{
			pthread_mutex_lock(l_fork);
			node->lock_status = LOCKED;
			if (node->next->lock_status == LOCKED)
			{
				pthread_mutex_unlock(l_fork);
				continue ;
			}
			pthread_mutex_lock(r_fork);
			node->next->lock_status = LOCKED;
			printer(node, "has taken a fork");
			printer(node, "has taken a fork");		
			check_death(node, ft_time());
			printer(node, "is eating");
			pthread_mutex_lock(&lockk);
			node->eaten_meals++;
			if (node->eaten_meals > max)
				max = node->eaten_meals;
			pthread_mutex_unlock(&lockk);
			pthread_mutex_unlock(&klop2);
			usleep(node->time_to_eat * 1000);
			node->time_left += ft_time();
			check_death(node, ft_time());
			pthread_mutex_unlock(l_fork);
			node->lock_status = UNLOCKED;
			pthread_mutex_unlock(r_fork);
			node->next->lock_status = UNLOCKED;
			printer(node, "is sleeping");
			usleep(node->time_to_sleep * 1000);
			node->old_status = THINKING_STATE;
			check_death(node, ft_time());
			// pthread_mutex_unlock(&klop5);
		}
		check_death(node, ft_time());
	}
	return (NULL);
}

void	check_death(t_list *node, time_t time)
{
	pthread_mutex_lock(&lock2);
	if (node->time_left <= time)
	{
		printf("%ld %lld died\n", time, node->philosopher_id);
		printf("===SUMULATION_ENDS==============\n");
		exit(0);
	}
	else
		pthread_mutex_unlock(&lock2);
}

void	printer(t_list *node, char *s)
{
	pthread_mutex_lock(&lock);
	printf("%ld %lld %s\n", ft_time(), node->philosopher_id, s);
	pthread_mutex_unlock(&lock);
}

t_data	init_mutexes(t_data data, t_params params)
{
	int		i;
	t_list	*n;

	i = 0;
	n = data.head;
	if (pthread_mutex_init(&lock, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&klop, NULL))
		ft_exit_with_error(MUTEXES, data);
	if (pthread_mutex_init(&lock2, NULL))
		ft_exit_with_error(MUTEXES, data);
	while (i < params.n_of_philos)
	{
		if (pthread_mutex_init(&n->l_fork, NULL))
			ft_exit_with_error(MUTEXES, data);
		i++;
		n = n->next;
	}
	return (data);
}

void	one_philosophe(t_data data, t_params params)
{
	(void)data;
	if (params.n_of_philos == 1)
	{
		if (params.t_to_think < ft_time())
		{
			printf("%ld 1 died\n", ft_time());
			printf("===SUMULATION_ENDS==============\n");
			exit(0);  
		}
		printf("%ld 1 is thinking\n", ft_time());
		usleep(params.t_to_think * 1000);
		printf("%ld 1 died\n", ft_time());
		printf("===SUMULATION_ENDS==============\n");
		exit(0);
	}
}