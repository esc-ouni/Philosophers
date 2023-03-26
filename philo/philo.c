/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:23:41 by idouni            #+#    #+#             */
/*   Updated: 2023/02/10 12:23:59 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	inspector(t_list *n , t_params params)
{
	int	i;

	i = 0;
	while (n && i < params.n_of_philos)
	{
		if (n->eat_state == EAT_ENOUGH)
		{
			i++;
			n->eat_state = DEATH;
		}
		n = n->next;
	}
	printf("===ALL_PHILOSOPHES_EAT_ENOUGH===\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list		*n;
	// int			i;
	t_params	params;
	t_data		data;

	// i = 0;
	data.head = NULL;
	data.mutexes = NULL;
	data.threads = NULL;
	params.n_of_philos = 0;
	if (ft_parse(data, &params, argc, argv))
		return (ft_exit_with_error(ARGS, data), 0);
	if (one_philosophe(data, params))
		return (0);
	if (create_philos(params, &data))
		return (ft_exit_with_error(MALLOC, data), 0);
	if (init_mutexes(&data, params))
		return (ft_exit_with_error(MUTEXES, data), 0);
	if (join_threads(&data, params))
		return (ft_exit_with_error(THREADS, data), 0);
	n = data.head;
	inspector(n , params);
	return (0);
}
