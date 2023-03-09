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

# include <unistd.h>
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
    pthread_mutex_t left_fork;
    int             time_life;
    int             time_slp;
    int             time_eat;
    int             time_thk;
    int             actual_state;
    int             old_state;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
    t_list  *head;
}   t_data;

typedef struct s_params
{
    int n_of_philos;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int n_of_meals;
}   t_params;

size_t ft_time();
t_data   create_philos(t_params params, t_data data);
t_list  *philosopher_state(t_params params, t_list *node);
void	*h_malloc(t_data data, size_t s, void *p);
void    tracker(t_params params, t_list *node);
t_params ft_parse(t_data data, t_params params, int argc, char **argv);
int     ft_atoi(t_data data, char *str);
int     ft_isdigit(int c);
void    ft_exit_with_error(t_data data);
t_list	*ft_lstnew(t_data data);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_data data, t_list **lst, t_list *new);

#endif
