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
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&lock2, NULL);

	t_params	params;
	t_data	data;
	data.head = NULL;
	params.n_of_philos = 0;
	params = ft_parse(data, params, argc, argv);
    printf("===SUMULATION_STARTS============\n");
	data = create_philo_container(params, data);
	// init_mutexes(data, params);
	join_threads(data, params);
	while (1);
	return (0);
}
