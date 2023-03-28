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
		usleep(node->time_left * 993);
		node->state = DEAD;
	}
	else
	{
		usleep(node->time_to_sleep * 993);
		node->think_state = THINKING_STATE;
	}
}

void	eat(t_list	*node)
{
	pthread_mutex_lock(node->l_fork);
	printer(node, "has taken a fork");
	pthread_mutex_lock(node->r_fork);
	printer(node, "has taken a fork");
	printer(node, "is eating");
	node->eaten_meals++;
	usleep(node->time_to_eat * 993);
	pthread_mutex_lock(&node->lock->lock1);
	node->time_left += ft_time() + 5;
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
	pthread_mutex_lock(&node->lock->lock2);
	node->eat_state = EAT_ENOUGH;
	pthread_mutex_unlock(&node->lock->lock2);
	return (NULL);
}

void	printer(t_list *node, char *s)
{
	pthread_mutex_lock(&node->lock->lock3);
	printf("%ld %d %s\n", ft_time(), node->philosopher_id, s);
	pthread_mutex_unlock(&node->lock->lock3);
}

void	cleaner(t_data data, t_params params)
{
	if (data.head)
		ft_lstclear(&data.head, params.n_of_philos);
	if (data.mutexes)
		free(data.mutexes);
	if (data.threads)
		free(data.threads);
}
