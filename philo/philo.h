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

# define EAT_ENOUGH 45

# define ALIVE 187
# define DEAD 190

# define THINKING_STATE 9
# define ALREADY_THINKING 0

# define ARGS 124
# define MALLOC 678
# define MUTEXES 897
# define THREADS 895

# define EATING 1
# define SLEEPING 2
# define THINKIG 3
# define DEATH 4

# define LOCKED 78
# define UNLOCKED 81

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

pthread_mutex_t	lock;
pthread_mutex_t	lock2;
pthread_mutex_t	lockk;
pthread_mutex_t	lokkkk;
pthread_mutex_t	lokkkk2;
pthread_mutex_t	klop;
pthread_mutex_t	klop2;
pthread_mutex_t	klop3;

typedef struct s_list
{
	pthread_t		philosopher;
	long long		philosopher_id;
	long long		time_to_think;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		num_of_meals;
	long long		time_left;
	long long		lock_status;
	long long		act_status;
	long long		old_status;
	long long		state;
	long long		eat_state;
	long long		eaten_meals;
	pthread_mutex_t	l_fork;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
	t_list			*head;
	pthread_mutex_t	*mutexes;
	pthread_t		*threads;
}	t_data;

typedef struct s_params
{
	long long	n_of_philos;
	long long	t_to_think;
	long long	t_to_eat;
	long long	t_to_sleep;
	long long	n_of_meals;
}	t_params;

time_t		ft_time(void);
t_data		init_mutexes(t_data data, t_params params);
t_data		create_philos(t_params params, t_data data);
void		printer(t_list *node, char *s);
void		check_death(t_list *node, time_t time);
t_data		join_threads(t_data data, t_params params);
void		one_philosophe(t_data data, t_params params);
void		*philosopher_state(void *arg);
void		*h_malloc(t_data data, size_t s, void *p);
t_params	ft_parse(t_data data, t_params params, int argc, char **argv);
int			ft_atoi(t_data data, char *str);
int			ft_isdigit(int c);
void		ft_exit_with_error(int  n, t_data data);
void		ft_exit(t_data data);
t_list		*ft_lstnew(t_data data);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst);
void		ft_lstadd_back(t_data data, t_list **lst, t_list *new);

#endif
