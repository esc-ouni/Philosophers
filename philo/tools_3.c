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

void	philosopher_state_2(void *arg)
{
	t_list			*node;

	node = arg;
	pthread_mutex_lock(node->l_fork);
	pthread_mutex_lock(node->r_fork);
	node->lock_status = LOCKED;
	node->next->lock_status = LOCKED;
	printer(node, "has taken a fork");
	printer(node, "has taken a fork");
	printer(node, "is eating");
	node->eaten_meals++;
	usleep(node->time_to_eat * 1000);
	node->time_left += ft_time();
	printer(node, "is sleeping");
	usleep(node->time_to_sleep * 1000);
	node->old_status = THINKING_STATE;
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
	node->lock_status = UNLOCKED;
	node->next->lock_status = UNLOCKED;
}

void	*philosopher_state(void *arg)
{
	t_list			*node;

	node = arg;
	node->l_fork = &node->fork;
	node->r_fork = &node->next->fork;
	node->eaten_meals = 0;	
	node->time_left = node->time_to_think;
	while (1)
	{
		if (node->eaten_meals == node->num_of_meals)
			break ;
		if (node->old_status == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->old_status = ALREADY_THINKING;
		}
		if (node->lock_status == UNLOCKED && \
		node->next->lock_status == UNLOCKED)
			philosopher_state_2(arg);
	}
	pthread_mutex_lock(&klop8);
	node->eat_state = EAT_ENOUGH;
	pthread_mutex_unlock(&klop8);
	pthread_mutex_unlock(&klop9);
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