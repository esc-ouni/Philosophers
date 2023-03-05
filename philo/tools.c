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

void	*h_malloc(t_data data, size_t s, void *p)
{
	p = malloc(s);
	if (!p)
	{
		ft_exit_with_error();
	}
	return (p);
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

void    state(void *arg)
{

}

void    create_philos(int n_of_philos)
{
    pthread_t ph[n_of_philos + 1];
    int i;

    i = 0;
    while (i <= n_of_philos)
    {
        pthread_create(ph[i], NULL, (void *)state, NULL);
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
