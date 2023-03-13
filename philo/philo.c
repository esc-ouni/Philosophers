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
	int	i	=	0;
	t_list	*n;
	t_params	params;
	t_data	data;

	data.head = NULL;
    printf("===SUMULATION_STARTS============\n");
	params.n_of_philos = 0;
	params = ft_parse(data, params, argc, argv);
	data = create_philo_container(params, data);
	// join_threads(data, params);
	// first_meal(params, data);
	n = data.head;

	while (n && i < params.n_of_philos)
    {
        pthread_join(&n->philosopher, NULL);
        n = n->next;
        i++;
    }

	// printf("\n\n===Sumulation======\n");
	// while(n && i < 200)
	// {
	// 	printf("philo_id       : %d\n",n->philosopher_id);
	// 	printf("left_fork      : %llu\n\n", n->l_fork);
	// 	n = n->next;
	// 	i++;
	// }
	while (1);
	return (0);
}
