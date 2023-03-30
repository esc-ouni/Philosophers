/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:44:20 by idouni            #+#    #+#             */
/*   Updated: 2023/03/30 18:44:23 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	inspector(t_data data, t_list *n, t_params params)
{
	int	i;

	i = 0;
	while (n && i < params.n_of_philos)
	{
		if (check_death(data, n, params))
		{
			cleaner(data, params);
			return (0);
		}
		pthread_mutex_lock(&n->lock->lock2);
		if (n->eat_state == EAT_ENOUGH)
		{
			i++;
			n->eat_state = STOP;
		}
		pthread_mutex_unlock(&n->lock->lock2);
		n = n->next;
	}
	cleaner(data, params);
	printf("===ALL_PHILOSOPHES_EAT_ENOUGH===\n");
	return (0);
}

void	printer(t_list *node, char *s)
{
	pthread_mutex_lock(&node->lock->lock3);
	printf("%ld ms\tphilosopher %d %s\n", ft_time(), node->philosopher_id, s);
	pthread_mutex_unlock(&node->lock->lock3);
}
