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

typedef struct s_locks
{
	pthread_mutex_t	lock1;
	pthread_mutex_t	lock2;
	pthread_mutex_t	lock3;
	pthread_mutex_t	lock4;
	pthread_mutex_t	lock5;
}	t_locks;

typedef struct s_list
{
	int				philosopher_id;
	int				time_to_think;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				time_left;
	int				state;
	int				think_state;
	int				eat_state;
	int				eaten_meals;
	pthread_t		philosopher;
	struct s_list	*next;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_locks			*lock;
}				t_list;

typedef struct s_params
{
	long long	n_of_philos;
	long long	t_to_think;
	long long	t_to_eat;
	long long	t_to_sleep;
	long long	n_of_meals;
}	t_params;

typedef struct s_data
{
	t_list			*head;
	pthread_mutex_t	*mutexes;
	pthread_t		*threads;
	t_params		params;
}	t_data;

typedef struct s_info
{
	pthread_t		*ph;
	pthread_mutex_t	*mt;
	t_list			*n;
}	t_info;

time_t		ft_time(void);
void		cleaner(t_data data, t_params params);
int			init_mutexes(t_data *data, t_params params);
int			create_philos(t_params params, t_data *data);
int			inspector(t_data data, t_list *n, t_params params);
void		printer(t_list *node, char *s);
void		check_death(t_list *node, time_t time);
int			join_threads(t_data *data, t_params params);
int			one_philosophe(t_data data, t_params params);
void		*philosopher_state(void *arg);
void		*h_malloc(t_data data, size_t s, void *p);
int			ft_parse(t_data data, t_params *params, int argc, char **argv);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
void		ft_exit_with_error(int n, t_data data);
t_list		*ft_lstnew(t_data data);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, int l);
void		ft_lstadd_back(t_list **lst, t_list *new);

#endif
