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
	check_death(node, ft_time());
	printer(node, "is sleeping");
	usleep(node->time_to_sleep * 1000);
	node->old_status = THINKING_STATE;
	check_death(node, ft_time());
	usleep(200);
}

void	eat(t_list	*node)
{
	check_death(node, ft_time());
	pthread_mutex_lock(node->l_fork);
	printer(node, "has taken a fork");
	check_death(node, ft_time());
	pthread_mutex_lock(node->r_fork);
	printer(node, "has taken a fork");
	printer(node, "is eating");
	node->eaten_meals++;
	usleep(node->time_to_eat * 1000);
	node->time_left += ft_time();
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
	check_death(node, ft_time());
}

void	*philosopher_state(void *arg)
{
	t_list			*node;

	node = arg;
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
		eat(arg);
		sleepp(arg);
	}
	pthread_mutex_lock(&node->lock->lock3);
	node->eat_state = EAT_ENOUGH;
	pthread_mutex_unlock(&node->lock->lock3);
	return (NULL);
}

void	check_death(t_list *node, time_t time)
{
	pthread_mutex_lock(&node->lock->lock4);
	if (node->time_left <= time)
	{
		usleep(100);
		printf("%ld %d died\n", time, node->philosopher_id);
		pthread_mutex_lock(&node->lock->lock5);
		node->state = DEAD;
		pthread_mutex_unlock(&node->lock->lock5);
		printf("===SUMULATION_ENDS==============\n");
	}
	else
		pthread_mutex_unlock(&node->lock->lock4);
}

void	printer(t_list *node, char *s)
{
	pthread_mutex_lock(&node->lock->lock2);
	printf("%ld %d %s\n", ft_time(), node->philosopher_id, s);
	pthread_mutex_unlock(&node->lock->lock2);
}