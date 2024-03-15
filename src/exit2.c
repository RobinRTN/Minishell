/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:16:08 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:35:20 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

long	ft_atoi_long(const char *str)
{
	int		i;
	int		sign;
	long	count;

	i = 0;
	count = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 34
		|| str[i] == 39 || str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = (count * 10) + (str[i] - 48);
		i++;
	}
	count = count * sign;
	return (count);
}

int	check_llong_max_b(char *num, int i)
{
	while (num[i])
	{
		if (num[i] > LLONG_MAX_STR[i])
			return (0);
		else if (num[i] < LLONG_MAX_STR[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_llong_max(char *num)
{
	int	i;

	i = 0;
	while ((num[i] == '-') || (num[i] == '+') || (num[i] == 34)
		|| (num[i] == 39))
	{
		if (num[i] == '-')
			return (1);
		i++;
	}
	if (ft_strlen(num) < 19)
		return (1);
	else if (ft_strlen(num) > 19)
		return (0);
	else
	{
		if (check_llong_max_b(num, i) == 1)
			return (1);
		else
			return (0);
	}
}
