/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:13:33 by idouni            #+#    #+#             */
/*   Updated: 2023/02/11 22:13:39 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	check_l(long long nb)
{
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

int	ft_atoi(char *str)
{
	int				i;
	long long		r;

	r = 0;
	i = 0;
	while ((str[i] == 45 || str[i] == 43))
	{
		if (str[i] == 45)
			return (-1);
		i++;
		if ((str[i] < 48 || str[i] > 57))
			return (-1);
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i++] - 48);
		r = check_l(r);
		if (r == -1)
			return (-1);
	}
	if (str[i] && (str[i] < 48 || str[i] > 57))
		return (-1);
	return (r);
}

void	*uno(void *arg)
{
	t_params	params;

	params = *(t_params *)arg;
	printf("===SUMULATION_STARTS============\n");
	if (params.t_to_think < ft_time())
	{
		printf("%ld 1 died\n", ft_time());
		printf("===SUMULATION_ENDS==============\n");
	}
	printf("%ld 1 is thinking\n", ft_time());
	usleep(params.t_to_think * 998);
	printf("%ld 1 died\n", ft_time());
	printf("===SUMULATION_ENDS==============\n");
	return (NULL);
}

int	one_philosophe(t_data data, t_params params)
{
	pthread_t	o_p;

	(void)data;
	if (params.n_of_philos == 1)
	{
		pthread_create(&o_p, NULL, uno, &params);
		pthread_join(o_p, NULL);
		return (1);
	}
	return (0);
}

int	inspector(t_data data, t_list *n, t_params params)
{
	int	i;

	i = 0;
	while (n && i < params.n_of_philos)
	{
		pthread_mutex_lock(&n->lock->lock1);
		if (n->time_left < ft_time())
		{
			printf("%ld %d died\n", ft_time(), n->philosopher_id);
			printf("===SUMULATION_ENDS==============\n");
			return (cleaner(data, params), 0);
		}
		pthread_mutex_unlock(&n->lock->lock1);
		pthread_mutex_lock(&n->lock->lock2);
		if (n->eat_state == EAT_ENOUGH)
		{
			i++;
			n->eat_state = DEATH;
		}
		pthread_mutex_unlock(&n->lock->lock2);
		n = n->next;
	}
	cleaner(data, params);
	printf("===ALL_PHILOSOPHES_EAT_ENOUGH===\n");
	return (0);
}
