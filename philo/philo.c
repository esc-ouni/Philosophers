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

int	main(int argc, char *argv[])
{
	t_list		*n;
	int			i;
	t_params	params;
	t_data		data;

	i = 0;
	data.head = NULL;
	data.mutexes = NULL;
	data.threads = NULL;
	params.n_of_philos = 0;
	if (ft_parse(data, &params, argc, argv))
	{
		ft_exit_with_error(ARGS, data);
		return (0);
	}
	if (one_philosophe(data, params))
		return (0);
	if (create_philos(params, &data))
	{
		ft_exit_with_error(THREADS, data);
		return (0);
	}
	if (init_mutexes(&data, params))
	{
		ft_exit_with_error(MUTEXES, data);
		return (0);
	}
	data = join_threads(data, params);
	n = data.head;
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
	exit(0);
	return (0);
}
