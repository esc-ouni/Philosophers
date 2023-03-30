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
	t_params	params;
	t_data		data;

	data.head = NULL;
	data.mutexes = NULL;
	data.threads = NULL;
	params.n_of_philos = 0;
	if (ft_parse(data, &params, argc, argv))
		return (ft_exit_with_error(ARGS, data), 1);
	data.params = params;
	if (one_philosophe(data, params))
		return (0);
	if (create_philos(params, &data))
		return (ft_exit_with_error(MALLOC, data), 1);
	if (init_mutexes(&data, params))
		return (ft_exit_with_error(MUTEXES, data), 1);
	if (join_threads(&data, params))
		return (ft_exit_with_error(THREADS, data), 1);
	n = data.head;
	inspector(data, n, params);
	return (0);
}

