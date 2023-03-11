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
    t_list  *n;
    int i;

    ph = NULL;
    ph = (pthread_t *)h_malloc(data, sizeof(pthread_t) * (params.n_of_philos + 1), ph);
    i = 0;
    if (!data.head)
    {
        data.head = ft_lstnew(data);
        data.head->philosopher_id = i + 1;
    }
    n = data.head->next;
    i++;
    while (i < (params.n_of_philos - 1))
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philosopher_id = i + 1;
        n = n->next;
        i++;
    }
    if (i == params.n_of_philos - 1)
    {
        n = ft_lstnew(data);
        ft_lstadd_back(data, &data.head, n);
        n->philosopher_id = i + 1;
        n->next = data.head;
    }
    free(ph);
    return (data);
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
    size_t t;
    t = ft_time();

    id = *(int   *)arg;
    return (NULL);
}