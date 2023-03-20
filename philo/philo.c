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
	t_list	*n;
	int 	i = 0;

	t_params	params;
	t_data	data;
	data.head = NULL;
	data.mutexes = NULL;
	data.threads = NULL;
	params.n_of_philos = 0;
	params = ft_parse(data, params, argc, argv);
    printf("===SUMULATION_STARTS============\n");
	one_philosophe(data, params);
	data = create_philo_container(params, data);
	data = join_threads(data, params);
	data = init_mutexes(data, params);
	n = data.head;

	while (n && i < params.n_of_philos)
	{
		if(n->eat_state == EAT_ENOUGH)
		{
			i++;
			n->eat_state = 4;
		}
		n = n->next;
	}
    printf("===ALL_PHILOSOPHES_EAT_ENOUGH===\n");
	exit(0);
	return (0);
}
