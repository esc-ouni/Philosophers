/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:35:31 by idouni            #+#    #+#             */
/*   Updated: 2023/03/22 10:35:47 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepp(t_list	*node)
{
	printer(node, "is sleeping");
	if (node->time_left < node->time_to_sleep)
	{
		ft_usleep(node->time_left);
		node->state = DEAD;
	}
	else
	{
		ft_usleep(node->time_to_sleep);
		node->think_state = THINKING_STATE;
	}
}

void	eat(t_list	*node)
{
	if (node->philosopher_id % 2 == 0)
		pthread_mutex_lock(node->l_fork);
	else
		pthread_mutex_lock(node->r_fork);
	printer(node, "has taken a fork");
	if (node->philosopher_id % 2 == 0)
		pthread_mutex_lock(node->r_fork);
	else
		pthread_mutex_lock(node->l_fork);
	printer(node, "has taken a fork");
	printer(node, "is eating");
	node->eaten_meals++;
	ft_usleep(node->time_to_eat);
	pthread_mutex_lock(&node->lock->lock1);
	node->time_left += ft_time();
	pthread_mutex_unlock(&node->lock->lock1);
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
}

void	*philosopher_state(void *arg)
{
	t_list			*node;

	node = arg;
	while (1)
	{
		pthread_mutex_lock(&node->lock->lock4);
		if (!node->keep_running)
		{
			break ;
		}
		pthread_mutex_unlock(&node->lock->lock4);
		if (node->eaten_meals == node->num_of_meals)
		{
			pthread_mutex_lock(&node->lock->lock2);
			node->eat_state = EAT_ENOUGH;
			pthread_mutex_unlock(&node->lock->lock2);
			break ;
		}
		if (node->think_state == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->think_state = ALREADY_THINKING;
		}
		eat(arg);
		sleepp(arg);
	}
	return (NULL);
}

void	ft_usleep(time_t time)
{
	time_t			d_time;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	d_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
	usleep((time - 20) * 1000);
	time += d_time;
	while (d_time < time)
	{
		gettimeofday(&tp, NULL);
		d_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
	}
}

void	cleaner(t_data data, t_params params)
{
	if (data.mutexes)
	{
		destroy_mutexes(data);
		free(data.mutexes);
	}
	if (data.threads)
		free(data.threads);
	if (data.head)
		ft_lstclear(&data.head, params.n_of_philos);
}
