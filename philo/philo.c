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

void	cleaner(t_data data, t_params params)
{
	if (data.head)
		ft_lstclear(&data.head, params);
	if (data.mutexes)
		free(data.mutexes);
	if (data.threads)
		free(data.threads);
}

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
		return (ft_exit_with_error(ARGS, data), 0);
	data.params = params;
	if (one_philosophe(data, params))
		return (0);
	if (create_philos(params, &data))
		return (ft_exit_with_error(MALLOC, data), 0);
	if (init_mutexes(&data, params))
		return (ft_exit_with_error(MUTEXES, data), 0);
	if (join_threads(&data, params))
		return (ft_exit_with_error(THREADS, data), 0);
	n = data.head;
	inspector(data, n , params);
}
