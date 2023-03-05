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

t_params ft_parse(t_params params, int argc, char **argv)
{
    (void)argv;
    if (argc < 5 || argc > 6)
        ft_exit_with_error();
    params.n_of_philos = ft_atoi(argv[1]);
    params.t_to_die = ft_atoi(argv[2]);
    params.t_to_eat = ft_atoi(argv[3]);
    params.t_to_sleep = ft_atoi(argv[4]);
    if (argc == 5)
        params.n_of_meals = -1;
    else
        params.n_of_meals = ft_atoi(argv[5]);
    return (params);
}

void    ft_exit()
{
    exit(0);
}

void    ft_exit_with_error()
{
    printf("==HINT=====================\n");
    printf("Program need at least 4 arguments specefied like this:\n");
    printf("Number_of_philos Time_to_die time_to_eat Time_to_sleep ");
    printf("Number_of_meals(opptional)\n");
    exit(1);
}