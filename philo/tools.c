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

int k = 1;

// time_t	p;
// time_t	p1;
// struct timezone tzp;
// struct timeval tp;

gettimeofday(&tp, &tzp);
p = tp.tv_sec;

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

void    state(void *arg)
{
    (void)arg;

    // gettimeofday(&tp, &tzp);
    // p1 = tp.tv_sec - p;
    // t_list *n = (t_list *)arg;
    printf("%lums philosopher %d is there\n",  k);
    k++;
}

t_data   create_philos(t_data data, int n_of_philos)
{
    pthread_t *ph;
    int i;

    ph = (pthread_t *)h_malloc(data, sizeof(pthread_t) * (n_of_philos + 1));
    i = 0;
    while (i < n_of_philos)
    {
        pthread_create(&ph[i], NULL, (void *)state, NULL);
        pthread_join(ph[i], NULL);
        i++;
    }
}

void    tracker(t_list *node)
{
    char s1[9] = "eating";
    char s2[9] = "thinking";
    char s3[9] = "sleeping";
    char s4[5] = "died";

    if (node->actual_state == 4)
    {
        printf("philosopher %d is %s\n", node->philo_id ,s4);
        exit(0);
    }
    if (node->old_state != node->actual_state && node->actual_state > 0)
    {
        if (node->actual_state == EATING)
            printf("philosopher %d is %s\n", node->philo_id ,s1);
        else if (node->actual_state == SLEEPING)
            printf("philosopher %d is %s\n", node->philo_id ,s3);
        else if (node->actual_state == THINKIG)
            printf("philosopher %d is %s\n", node->philo_id ,s2);
    }
}

// t_list  philosopher_state(t_list *node)
// {
//     if 
//     return (node);
// }

void	*h_malloc(t_data data, size_t s, void *p)
{
    (void)data;

	p = malloc(s);
	if (!p)
	{
		ft_exit_with_error();
	}
	return (p);
}