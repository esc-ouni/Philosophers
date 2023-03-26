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
	data.threads = NULL;
	params.n_of_philos = 0;
	ft_parse(data, &params, argc, argv);
	printf("===SUMULATION_STARTS============\n");
	one_philosophe(data, params);
	data = create_philos(params, data);
	data = init_mutexes(data, params);
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
