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
	// int	i	=	0;
	t_list	*n;
	t_params	params;
	t_data	data;

	data.head = NULL;
	params.n_of_philos = 0;
	params = ft_parse(data, params, argc, argv);
    printf("===SUMULATION_STARTS============\n");
	data = create_philo_container(params, data);
	first_meal(params, data);
	join_threads(data, params);
	n = data.head;

	// printf("\n\n===Sumulation======\n");
	while(n)
	{
		if (n->state == DEAD)
		{
			printf("===SUMULATION_ENDS==============\n");
			// pthread_exit(NULL);
			exit(1);
		}
		n = n->next;
	}
	// while (1);
	return (0);
}
