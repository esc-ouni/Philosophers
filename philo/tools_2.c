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

t_data   create_philo_container(t_params params, t_data data)
{
    pthread_t *ph;
    pthread_mutex_t *mt;
    t_list  *n;
    int i;

    ph = NULL;
    ph = (pthread_t *)h_malloc(data, sizeof(pthread_t) * (params.n_of_philos + 1), ph);
    mt = (pthread_mutex_t *)h_malloc(data, sizeof(pthread_mutex_t) * (params.n_of_philos + 1), ph);

    i = 0;
    if (!data.head)
    {
        data.head = ft_lstnew(data);
        data.head->philosopher_id = i + 1;
        data.head->l_fork = mt[i];
        data.head->time_to_think = params.t_to_think;
        data.head->time_to_sleep = params.t_to_sleep;
        data.head->time_to_eat = params.t_to_eat;
        pthread_create(&ph[i], NULL, philosopher_state, (void *)data.head);
        data.head->philosopher = ph[i];
    }
    n = data.head->next;
    i++;
    while (i < (params.n_of_philos - 1))
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philosopher_id = i + 1;
        n->l_fork = mt[i];
        n->time_to_think = params.t_to_think;
        n->time_to_sleep = params.t_to_sleep;
        n->time_to_eat = params.t_to_eat;
        pthread_create(&ph[i], NULL, philosopher_state, (void *)n);
        n->philosopher = ph[i];
        n = n->next;
        i++;
    }
    if (i == params.n_of_philos - 1)
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philosopher_id = i + 1;
        n->l_fork = mt[i];
        n->time_to_think = params.t_to_think;
        n->time_to_sleep = params.t_to_sleep;
        n->time_to_eat = params.t_to_eat;
        pthread_create(&ph[i], NULL, philosopher_state, (void *)n);
        n->philosopher = ph[i];
        n->next = data.head;
    }
    // free(ph);
    return (data);
}

void  join_threads(t_data data, t_params params)
{
    int i;
    t_list  *n;

    i = 0;
    n = data.head;
    while (n && i < params.n_of_philos)
    {
        pthread_detach(n->philosopher);
        n = n->next;
        i++;
    }
    // return (data);
}

void    first_meal(t_params params, t_data data)
{
    (void)data;
    (void)params;
    //first_meal
}

void  *philosopher_state(void *arg)
{
    int id;
    t_list  *node;
    ft_time();

    node = (t_list  *)arg;
    id = node->philosopher_id;
    node->time_left = node->time_to_think + node->time_to_sleep;
    check_death(node);

    while (1)
    {
        // check_death(node);

        printf("%ld %lld is thinking\n", ft_time(), node->philosopher_id);
        check_death(node);
        
        pthread_mutex_init(&node->l_fork, NULL);
	    if (node->philosopher_id % 2 == 0)
        {
            pthread_mutex_lock(&node->next->l_fork);
            printf("%ld %lld has taken a fork\n", ft_time(), node->philosopher_id);
            check_death(node);
        }
        else
        {
            pthread_mutex_lock(&node->l_fork);
            printf("%ld %lld has taken a fork\n", ft_time(), node->philosopher_id);
            check_death(node);
        }
        if (node->philosopher_id % 2 == 0)
        {
            pthread_mutex_lock(&node->l_fork);
            printf("%ld %lld has taken a fork\n", ft_time(), node->philosopher_id);
            check_death(node);
        }
        else
        {
            pthread_mutex_lock(&node->next->l_fork);
            printf("%ld %lld has taken a fork\n", ft_time(), node->philosopher_id);
            check_death(node);
        }

        printf("%ld %lld is eating\n", ft_time(), node->philosopher_id);
        node->time_left += ft_time();
        usleep(node->time_to_eat * 1000);
        check_death(node);

        pthread_mutex_unlock(&node->l_fork);
        pthread_mutex_unlock(&node->next->l_fork);
        check_death(node);

        printf("%ld %lld is sleeping\n", ft_time(), node->philosopher_id);
        usleep(node->time_to_sleep * 1000);
        check_death(node);
        // continue ;
        
    }
    return (NULL);
}

void    check_death(t_list *node)
{
    pthread_mutex_t lock;

    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
    if (node->time_left < ft_time())
    {
        printf("%ld %lld died\n", ft_time(), node->philosopher_id);
        printf("===SUMULATION_ENDS==============\n");
        exit(0);
        pthread_mutex_lock(&lock);
    }
    // pthread_mutex_unlock(&lock);
}

void    printer(t_list *node, char *s)
{
    pthread_mutex_t lock;

    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
    printf("%ld %lld %s\n", ft_time(), node->philosopher_id, s);
    pthread_mutex_unlock(&lock);
}
