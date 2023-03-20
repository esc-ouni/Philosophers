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

t_data   create_philos(t_params params, t_data data)
{
    pthread_t *ph;
    pthread_mutex_t *mt;
    t_list  *n;
    int i;

    ph = NULL;
    mt = NULL;
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
        data.head->num_of_meals = params.n_of_meals;
        data.head->lock_status = UNLOCKED;
        data.head->old_status = 9;
        if (pthread_create(&ph[i], NULL, philosopher_state, (void *)data.head))
            ft_exit_with_error(THREADS, data);
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
        n->num_of_meals = params.n_of_meals;
        if (pthread_create(&ph[i], NULL, philosopher_state, (void *)n))
            ft_exit_with_error(THREADS, data);
        n->lock_status = UNLOCKED;
        n->old_status = 9;
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
        n->num_of_meals = params.n_of_meals;
        n->lock_status = UNLOCKED;
        n->old_status = 9;
        if (pthread_create(&ph[i], NULL, philosopher_state, (void *)n))
            ft_exit_with_error(THREADS, data);
        n->philosopher = ph[i];
        n->next = data.head;
    }
    data.mutexes = mt;
    data.threads = ph;
    return (data);
}

t_data  join_threads(t_data data, t_params params)
{
    int i;
    t_list  *n;

    ft_time();
    i = 0;
    n = data.head;
    while (n && i < params.n_of_philos)
    {
        if (pthread_detach(n->philosopher))
            ft_exit_with_error(THREADS, data);
        n = n->next;
        i++;
    }
    return (data);
}


void  *philosopher_state(void *arg)
{
    int i;
    int n;
    int id;
    t_list  *node;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;

    i = 0;
    n = 0;
    ft_time();
    node = (t_list  *)arg;
    l_fork = &node->l_fork;
    r_fork = &node->next->l_fork;
    id = node->philosopher_id;
    node->time_left = node->time_to_think;
    // node->num_of_meals = 0;
    // printf("\n\n%lld\n\n", node->num_of_meals);
    while (1)
    {
        if (i == node->num_of_meals)
        {
            node->eat_state = EAT_ENOUGH;
            break;
        }
        check_death(node, ft_time());
        if (node->old_status == THINKING_STATE)
        {
            printer(node, "is thinking");
            node->old_status = ALREADY_THINKING;
        }
        check_death(node, ft_time());

        if (node->lock_status == UNLOCKED && node->next->lock_status == UNLOCKED)
        {
            pthread_mutex_lock(l_fork);
            node->lock_status = LOCKED;
            if (node->next->lock_status == LOCKED)
            {
                pthread_mutex_unlock(l_fork);
                continue;
            }
            pthread_mutex_lock(r_fork);
            node->next->lock_status = LOCKED;
            printer(node, "has taken a fork");
            printer(node, "has taken a fork");
        
            check_death(node, ft_time());

            printer(node, "is eating");
            i++;
            usleep(node->time_to_eat * 1000);
            node->time_left += ft_time();
            check_death(node, ft_time());

            pthread_mutex_unlock(l_fork);
            node->lock_status = UNLOCKED;
            pthread_mutex_unlock(r_fork);
            node->next->lock_status = UNLOCKED;
            printer(node, "is sleeping");
            usleep(node->time_to_sleep * 1000);
            node->old_status = THINKING_STATE;
            check_death(node, ft_time());
        }
        check_death(node, ft_time());
    }
    return (NULL);
}

void    check_death(t_list *node, time_t time)
{
    pthread_mutex_lock(&lock2);
    if (node->time_left <= time)
    {
        printf("%ld %lld died\n", time, node->philosopher_id);
        printf("===SUMULATION_ENDS==============\n");
        exit(0);
    }
    else
        pthread_mutex_unlock(&lock2);
}

void    printer(t_list *node, char *s)
{
    pthread_mutex_lock(&lock);
    printf("%ld %lld %s\n", ft_time(), node->philosopher_id, s);
    pthread_mutex_unlock(&lock);
}

t_data        init_mutexes(t_data data, t_params params)
{
    int i;
    t_list  *n;

    i = 0;
    n = data.head;
    if (pthread_mutex_init(&lock, NULL))
        ft_exit_with_error(MUTEXES, data);
    if (pthread_mutex_init(&lock2, NULL))
        ft_exit_with_error(MUTEXES, data);
    while(i < params.n_of_philos)
    {
        if(pthread_mutex_init(&n->l_fork, NULL))
            ft_exit_with_error(MUTEXES, data);
        i++;
        n = n->next;
    }
    return(data);
}

void    one_philosophe(t_data data, t_params params)
{
    (void)data;
    if (params.n_of_philos == 1)
    {
        if (params.t_to_think < ft_time())
        {
            printf("%ld 1 died\n", ft_time());
            printf("===SUMULATION_ENDS==============\n");
            exit(0);  
        }
        printf("%ld 1 is thinking\n", ft_time());
        usleep(params.t_to_think * 1000);
        printf("%ld 1 died\n", ft_time());
        printf("===SUMULATION_ENDS==============\n");
        exit(0);
    }
}