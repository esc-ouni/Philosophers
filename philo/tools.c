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

t_params ft_parse(t_data data, t_params params, int argc, char **argv)
{
    (void)argv;
    if (argc < 5 || argc > 6)
        ft_exit_with_error(data);
    params.n_of_philos = ft_atoi(data, argv[1]);
    params.t_to_die = ft_atoi(data, argv[2]);
    params.t_to_eat = ft_atoi(data, argv[3]);
    params.t_to_sleep = ft_atoi(data, argv[4]);
    if (argc == 5)
        params.n_of_meals = -1;
    else
        params.n_of_meals = ft_atoi(data, argv[5]);
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

size_t ft_time(size_t init_time)
{
    struct timeval    tp;
    struct timezone    tzp;
    size_t   t;

    gettimeofday(&tp, &tzp);
    t = (tp.tv_usec - init_time) / 1000;

    return (t);
}

void    state(void *arg)
{
    size_t t;
    t = ft_time(*(size_t  *)arg);
    printf("%zums philosopher created\n", t);
    // usleep(3000);
    while (1);
}

t_data   create_philos(t_data data, int n_of_philos)
{
    struct timeval    tp;
    struct timezone    tzp;
    size_t        t;
    pthread_t *ph;
    t_list  *n;
    int i;

    gettimeofday(&tp, &tzp);
    t = (size_t)tp.tv_usec;
    ph = NULL;
    ph = (pthread_t *)h_malloc(data, sizeof(pthread_t) * (n_of_philos + 1), ph);
    i = 0;
    if (!data.head)
    {
        data.head = ft_lstnew(data);
        data.head->philo_id = i + 1;
        pthread_create(&ph[i], NULL, (void *)state, &t);
        // pthread_join(ph[i], NULL);
        pthread_detach(ph[i]);
        data.head->philosopher = ph[i];
    }
    i++;
    while (i < n_of_philos - 1)
    {
        ft_lstadd_back(data, &data.head, ft_lstnew(data));
        n = data.head->next;
        n->philo_id = i + 1;
        pthread_create(&ph[i], NULL, (void *)state, &t);
        // pthread_join(ph[i], NULL);
        pthread_detach(ph[i]);
        n->philosopher = ph[i];
        n->actual_state = -1;
        // n->left_fork = 0;
        n = n->next;
        i++;
    }
    // if (i == n_of_philos - 1)
    // {
    //     ft_lstadd_back(data, &data.head, ft_lstnew(data));
    //     n = data.head->next;
    //     n->philo_id = i + 1;
    //     pthread_create(&ph[i], NULL, (void *)state, &t);
    //     // pthread_join(ph[i], NULL);
    //     pthread_detach(ph[i]);
    //     n->philosopher = ph[i];
    //     n->actual_state = -1;
    //     // n->left_fork = 0;
    //     n->next = data.head;
    // }
    free(ph);
    return (data);
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
		ft_exit_with_error(data);
	}
	return (p);
}