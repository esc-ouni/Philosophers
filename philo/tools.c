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
    if (argc == 5)
        data.n_of_meals = -1;
    else
        data.n_of_meals = ft_atoi(argv[5]);
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