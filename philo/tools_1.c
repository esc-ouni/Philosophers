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

char	*check(t_data data, char *str)
{
	int	i;

	i = 0;
	if (str[0] == 45 || str[0] == 43 || str[0] == 48)
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_exit_with_error(ARGS, data);
		i++;
	}
	return (str);
}

long long	check_l(t_data data, long long nb, int s)
{
	if (nb > 2147483647 && s == 1)
		ft_exit_with_error(ARGS, data);
	else if (nb > 2147483648 && s == -1)
		ft_exit_with_error(ARGS, data);
	return (nb);
}

int	ft_atoi(t_data data, char *str)
{
	int				i;
	long long		r;
	int				s;

	s = 1;
	r = 0;
	i = 0;
	str = check(data, str);
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
		r = r * 10 + (str[i] - 48);
		r = check_l(data, r, s);
		i++;
	}
	return (r * s);
}

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}
