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
	params.n_of_philos = 0;
	params = ft_parse(data, params, argc, argv);
	data = create_philos(params, data);
	n = data.head;
	// while (n)
	// {
	// 	tracker(params, n);
	// 	n = n->next;
	// }

	printf("\n\n===Sumulation======\n");
	while(n && i < 7)
	{
		printf("philo_id       : %d\n",n->philo_id);
		printf("actual_state   : %d\n",n->actual_state);
		// printf("old_state      : %d\n",n->old_state);
		// printf("thread id      : %d\n",n->philosopher);
		printf("time remains   : %d\n",n->time_life);
		printf("next thread id : %d\n\n",n->next->philo_id);
		n = n->next;
		i++;
	}
	return (0);
}
