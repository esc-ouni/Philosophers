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
    long long       philosopher_id;
    long long       time_to_think;
    long long       time_to_eat;
    long long       time_to_sleep;
    long long       num_of_meals;
    pthread_mutex_t l_fork;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
    t_list  *head;
}   t_data;

typedef struct s_params
{
    long long n_of_philos;
    long long t_to_think;
    long long t_to_eat;
    long long t_to_sleep;
    long long n_of_meals;
}   t_params;

time_t      ft_time();
void        first_meal(t_params params, t_data data);
t_data      create_philo_container(t_params params, t_data data);
// t_data      create_threads(t_data data, t_params params);
void        join_threads(t_data data, t_params params);
void        *philosopher_state(void *arg);
void	    *h_malloc(t_data data, size_t s, void *p);
t_params    ft_parse(t_data data, t_params params, int argc, char **argv);
int         ft_atoi(t_data data, char *str);
int         ft_isdigit(int c);
void        ft_exit_with_error(t_data data);
t_list	    *ft_lstnew(t_data data);
t_list	    *ft_lstlast(t_list *lst);
void	    ft_lstclear(t_list **lst);
void	    ft_lstadd_back(t_data data, t_list **lst, t_list *new);
t_list	    *search_by_id(int id, t_list *node);

#endif
