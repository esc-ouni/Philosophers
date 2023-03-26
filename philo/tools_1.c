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

long long	check_l(t_data data, long long nb)
{
	if (nb > 2147483647)
		ft_exit_with_error(ARGS, data);
	return (nb);
}

int	ft_atoi(t_data data, char *str)
{
	int				i;
	long long		r;

	r = 0;
	i = 0;
	while ((str[i] == 45 || str[i] == 43))
	{
		if (str[i] == 45)
			ft_exit_with_error(ARGS, data);
		i++;
		if ((str[i] < 48 || str[i] > 57))
			ft_exit_with_error(ARGS, data);
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i++] - 48);
		r = check_l(data, r);
		// i++;
	}
	if (str[i] && (str[i] < 48 || str[i] > 57))
		ft_exit_with_error(ARGS, data);
	return (r);
}

void	one_philosophe(t_data data, t_params params)
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