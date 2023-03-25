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
	usleep(node->time_to_sleep * 1000);
	node->old_status = THINKING_STATE;
}

void	eat(t_list	*node)
{
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
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
	node->lock_status = UNLOCKED;
	node->next->lock_status = UNLOCKED;
}
void	pickup_forks(t_list	*node)
{
	if (node->next->lock_status == LOCKED)
		pthread_mutex_unlock(&node->fork);
			node->lock_status = UNLOCKED;
}

void	*philosopher_state(void *arg)
{
	t_list			*node;

	node = arg;
	node->l_fork = &node->fork;
	node->r_fork = &node->next->fork;
	while (1)
	{
		check_death(node, ft_time());
		if (node->eaten_meals == node->num_of_meals)
			break ;
		if (node->old_status == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->old_status = ALREADY_THINKING;
		}
		check_death(node, ft_time());
		pickup_forks(arg);
		check_death(node, ft_time());
		if (node->lock_status == UNLOCKED && \
		node->next->lock_status == UNLOCKED)
		{
			eat(arg);
			check_death(node, ft_time());
			sleepp(arg);
			check_death(node, ft_time());
		}
	}
	node->eat_state = EAT_ENOUGH;
	return (NULL);
}

void	check_death(t_list *node, time_t time)
{
	pthread_mutex_lock(&lock1);
	if (node->time_left <= time)
	{
		printf("%ld %d died\n", time, node->philosopher_id);
		printf("===SUMULATION_ENDS==============\n");
		exit(0);
	}
	else
		pthread_mutex_unlock(&lock1);
}

void	printer(t_list *node, char *s)
{
	printf("%ld %d %s\n", ft_time(), node->philosopher_id, s);
}