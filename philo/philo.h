/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:22:12 by idouni            #+#    #+#             */
/*   Updated: 2023/02/10 12:22:58 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_data
{
    int n_of_philos;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int n_of_meals;
}   t_data;

t_data  ft_parse(t_data data, int argc, char **args);
int     ft_atoi(char *str);
int     ft_isdigit(int c);
void    ft_exit();
void    ft_exit_with_error();


#endif
