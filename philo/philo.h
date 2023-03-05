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

# define EATING 1
# define SLEEPING 2 
# define THINKIG 3
# define DEATH 4

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_list
{
	pthread_t       philosopher;
    int             philo_id;
    int             fork;
    int             time_life;
    int             old_state;
    int             actual_state;
	struct s_list	*next;
	struct s_list	*previous;
}				t_list;

typedef struct s_params
{
    int n_of_philos;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int n_of_meals;
}   t_params;

void    create_philos(int n_of_philos);
t_list  philosopher_state(t_list *node);
void	*h_malloc(size_t s, void *p);
void    tracker(t_list *node);
t_params  ft_parse(t_params params, int argc, char **args);
int     ft_atoi(char *str);
int     ft_isdigit(int c);
void    ft_exit();
void    ft_exit_with_error();


#endif
