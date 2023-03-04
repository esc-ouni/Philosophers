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

t_data  ft_parse(t_data data, int argc, char **argv)
{
    (void)argv;
    if (argc < 5 || argc > 6)
        ft_exit_with_error();
    data.n_of_philos = ft_atoi(argv[1]);
    data.t_to_die = ft_atoi(argv[2]);
    data.t_to_eat = ft_atoi(argv[3]);
    data.t_to_sleep = ft_atoi(argv[4]);
    if (argc == 5)
        data.n_of_meals = -1;
    else
        data.n_of_meals = ft_atoi(argv[5]);
    printf("okay data.n_of_philos %d\n", data.n_of_philos);
    printf("okay data.t_to_die %d\n", data.t_to_die);
    printf("okay data.t_to_eat %d\n", data.t_to_eat);
    printf("okay data.t_to_sleep %d\n", data.t_to_sleep);
    printf("okay n of meals %d\n", data.n_of_meals);
    exit(0);
    return (data);
}

void    ft_exit()
{
    exit(0);
}

void    ft_exit_with_error()
{
    printf("errorrn\n");
    exit(1);
}