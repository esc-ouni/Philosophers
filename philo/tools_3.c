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
		usleep(node->time_left * 1000);
		node->state = DEAD;
		usleep(1000);
	}
	usleep(node->time_to_sleep * 1000);
	node->think_state = THINKING_STATE;
	usleep(200);	
}

void	eat(t_list	*node)
{
	pthread_mutex_lock(node->l_fork);
	printer(node, "has taken a fork");
	pthread_mutex_lock(node->r_fork);
	printer(node, "has taken a fork");
	printer(node, "is eating");
	node->eaten_meals++;
	usleep(node->time_to_eat * 1000);
	node->time_left += ft_time();
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
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
		if (node->think_state == THINKING_STATE)
		{
			printer(node, "is thinking");
			node->think_state = ALREADY_THINKING;
		}
		eat(arg);
		sleepp(arg);
	}
	node->eat_state = EAT_ENOUGH;
	return (NULL);
}

void	check_death(t_list *node, time_t time)
{
	pthread_mutex_lock(&node->lock->lock1);
	if (node->time_left < time)
	{
		node->state = DEAD;
	}
	else
		pthread_mutex_unlock(&node->lock->lock1);
}

void	printer(t_list *node, char *s)
{
	printf("%ld %d %s\n", ft_time(), node->philosopher_id, s);
}