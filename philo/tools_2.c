/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:39:36 by idouni            #+#    #+#             */
/*   Updated: 2023/03/11 17:39:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data   create_philo_continer(t_params params, t_data data)
{
    struct timeval    tp;
    struct timezone    tzp;
    pthread_t *ph;
    t_list  *n;
    int i;

    ph = NULL;
    ph = (pthread_t *)h_malloc(data, sizeof(pthread_t) * (params.n_of_philos + 1), ph);
    i = 0;
    if (!data.head)
    {
        data.head = ft_lstnew(data);
        data.head->philo_id = i + 1;
        data.head->philosopher = ph[i];
        data.head->actual_state = -1;
        data.head->time_life = params.t_to_die + params.t_to_sleep;
        data.head->time_eat = params.t_to_eat;
        data.head->time_thk = params.t_to_die;
        data.head->time_slp = params.t_to_sleep;
        data.head->left_fork = 1;
    }
    n = data.head->next;
    i++;
    while (i < (params.n_of_philos - 1))
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philo_id = i + 1;
        n->philosopher = ph[i];
        n->actual_state = -1;
        n->time_life = params.t_to_die + params.t_to_sleep;
        n->time_eat = params.t_to_eat;
        n->time_thk = params.t_to_die;
        n->time_slp = params.t_to_sleep;
        n->left_fork = 1;
        n = n->next;
        i++;
    }
    if (i == params.n_of_philos - 1)
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philo_id = i + 1;
        n->philosopher = ph[i];
        n->actual_state = -1;
        n->time_life = params.t_to_die + params.t_to_sleep;
        n->time_eat = params.t_to_eat;
        n->time_thk = params.t_to_die;
        n->time_slp = params.t_to_sleep;
        n->left_fork = 1;
        n->next = data.head;
    }
    free(ph);
    return (data);
}

void    tracker(t_params params, t_list *node)
{
    char s1[9] = "eating";
    char s2[9] = "thinking";
    char s3[9] = "sleeping";
    char s4[5] = "died";

    philosopher_state(params, node);
    if (node->actual_state == 4)
    {
        printf("%zums philosopher %d is %s\n",ft_time() ,node->philo_id ,s4);
        printf("===SUMULATION_ENDS=============\n");
        exit(0);
    }
    else if (node->old_state != node->actual_state)
    {
        if (node->old_state != node->actual_state && node->actual_state > 0)
        {
            if (node->actual_state == EATING)
                printf("%zums philosopher %d is %s\n",ft_time() ,node->philo_id ,s1);
            else if (node->actual_state == SLEEPING)
                printf("%zums philosopher %d is %s\n",ft_time() ,node->philo_id ,s3);
            else if (node->actual_state == THINKIG)
                printf("%zums philosopher %d is %s\n",ft_time() ,node->philo_id ,s2);
        }
        node->old_state = node->actual_state;
    }
}

void    first_meal(t_params params, t_data data)
{
    int i;
    t_list  *n;

    i = 0;
    n = data.head;
    if (n->time_life <= ft_time())
        n->actual_state = 4;
    while (++i < params.n_of_philos && n)
    {
        if (n->philo_id % 2)
            n->actual_state = 1;
        n = n->next;
    }
}

t_list  *philosopher_state(t_params params, t_list *node)
{
    size_t t;
    t = ft_time();

    if (node->time_life <= ft_time())
        node->actual_state = 4;
    else if (node->old_state == 1 && node->time_life <= ft_time())
        node->actual_state = 4;
    else if (node->actual_state == -1)
    {
        node->actual_state = 3;
        usleep(800);
        node->time_life = params.t_to_die + params.t_to_sleep;
        if (node->time_life < t)
            node->actual_state = 4;
    }
    else if (node->left_fork && node->next->left_fork)
    {
        node->actual_state = 1;
        node->time_life = params.t_to_die + params.t_to_sleep;
    }
    return (node);
}