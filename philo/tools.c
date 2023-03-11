/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:36:47 by idouni            #+#    #+#             */
/*   Updated: 2023/02/10 12:37:03 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_params ft_parse(t_data data, t_params params, int argc, char **argv)
{
    (void)argv;
    if (argc < 5 || argc > 6)
        ft_exit_with_error(data);
    params.n_of_philos = ft_atoi(data, argv[1]);
    params.t_to_think = ft_atoi(data, argv[2]);
    params.t_to_eat = ft_atoi(data, argv[3]);
    params.t_to_sleep = ft_atoi(data, argv[4]);
    if (argc == 5)
        params.n_of_meals = -1;
    else
        params.n_of_meals = ft_atoi(data, argv[5]);
    return (params);
}


void    ft_exit(t_data data)
{
    if (data.head)
        ft_lstclear(&data.head);
    exit(0);
}

void    ft_exit_with_error(t_data data)
{
    if (data.head)
        ft_lstclear(&data.head);
    printf("==HINT=====================\n");
    printf("Program need at least 4 arguments specefied like this:\n");
    printf("Number_of_philos Time_to_die time_to_eat Time_to_sleep ");
    printf("Number_of_meals(opptional)\n");
    exit(1);
}

time_t ft_time()
{
    static time_t init_time;
    struct timeval    tp;
    time_t   t;

    gettimeofday(&tp, NULL);
    if (!init_time)
        init_time = (time_t)(tp.tv_sec * 1000) + (time_t)(tp.tv_usec / 1000);
    t = (((time_t)(tp.tv_usec / 1000) + (time_t)tp.tv_sec * 1000) - init_time);
    return (t);
}

void	*h_malloc(t_data data, size_t s, void *p)
{
    (void)data;

	p = malloc(s);
	if (!p)
	{
		ft_exit_with_error(data);
	}
	return (p);
}