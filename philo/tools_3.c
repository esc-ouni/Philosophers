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

void    philosopher_state_2(void *arg)
{
	int				max;
	int				id;
	t_list			*node;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	// t_list			*node;

	max = 0;
	node = (t_list  *)arg;
	l_fork = &node->l_fork;
	r_fork = &node->next->l_fork;
	id = node->philosopher_id;
	node->eaten_meals = 0;
	node->time_left = node->time_to_think;

	node = (t_list  *)arg;
	if (node->lock_status == UNLOCKED && \
	node->next->lock_status == UNLOCKED && node->eaten_meals <= max)
	{
		pthread_mutex_lock(l_fork);
		node->lock_status = LOCKED;
		if (node->next->lock_status == LOCKED)
		{
			pthread_mutex_unlock(l_fork);
			// continue ;
		}
		pthread_mutex_lock(r_fork);
		node->next->lock_status = LOCKED;
		printer(node, "has taken a fork");
		printer(node, "has taken a fork");		
		printer(node, "is eating");
		node->eaten_meals++;
		if (node->eaten_meals > max)
			max = node->eaten_meals;
		usleep(node->time_to_eat * 1000);
		node->time_left += ft_time();
		pthread_mutex_unlock(l_fork);
		node->lock_status = UNLOCKED;
		pthread_mutex_unlock(r_fork);
		node->next->lock_status = UNLOCKED;
		printer(node, "is sleeping");
		usleep(node->time_to_sleep * 1000);
		node->old_status = THINKING_STATE;
	}
}

void	*philosopher_state(void *arg)
{
	int				max;
	int				id;
	t_list			*node;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	// printf("\n%p\n%p\n%p\n%p\n\n", max, id, node, l_fork, r_fork);

	ft_time();
	max = 0;
	node = (t_list  *)arg;
	l_fork = &node->l_fork;
	r_fork = &node->next->l_fork;
	id = node->philosopher_id;
	node->eaten_meals = 0;
	node->time_left = node->time_to_think;
	while (1)
	{
		if (node->eaten_meals == node->num_of_meals)
		{
			node->eat_state = EAT_ENOUGH;
			break ;
		}
		if (node->old_status == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->old_status = ALREADY_THINKING;
		}
		philosopher_state_2(arg);
		// if (node->lock_status == UNLOCKED && \
		// node->next->lock_status == UNLOCKED && node->eaten_meals <= max)
		// {
		// 	pthread_mutex_lock(l_fork);
		// 	node->lock_status = LOCKED;
		// 	if (node->next->lock_status == LOCKED)
		// 	{
		// 		pthread_mutex_unlock(l_fork);
		// 		continue ;
		// 	}
		// 	pthread_mutex_lock(r_fork);
		// 	node->next->lock_status = LOCKED;
		// 	printer(node, "has taken a fork");
		// 	printer(node, "has taken a fork");		
		// 	printer(node, "is eating");
		// 	node->eaten_meals++;
		// 	if (node->eaten_meals > max)
		// 		max = node->eaten_meals;
		// 	usleep(node->time_to_eat * 1000);
		// 	node->time_left += ft_time();
		// 	pthread_mutex_unlock(l_fork);
		// 	node->lock_status = UNLOCKED;
		// 	pthread_mutex_unlock(r_fork);
		// 	node->next->lock_status = UNLOCKED;
		// 	printer(node, "is sleeping");
		// 	usleep(node->time_to_sleep * 1000);
		// 	node->old_status = THINKING_STATE;
	}
	return (NULL);
}

void	check_death(t_list *node, time_t time)
{
	pthread_mutex_lock(&lock2);
	if (node->time_left <= time)
	{
		printf("%ld %d died\n", time, node->philosopher_id);
		printf("===SUMULATION_ENDS==============\n");
		exit(0);
	}
	else
		pthread_mutex_unlock(&lock2);
}

void	printer(t_list *node, char *s)
{
	pthread_mutex_lock(&lock);
	printf("%ld %d %s\n", ft_time(), node->philosopher_id, s);
	pthread_mutex_unlock(&lock);
}