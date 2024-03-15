/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:32:10 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:36:16 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_llong_min_b(char *num, int i)
{
	while (num[i])
	{
		if (num[i] > LLONG_MIN_STR[i])
			return (0);
		else if (num[i] < LLONG_MIN_STR[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_llong_min(char *num)
{
	int	i;
	int	is_minus;

	i = 1;
	is_minus = 0;
	while ((num[i] == '-') || (num[i] == '+') || (num[i] == 34)
		|| (num[i] == 39))
	{
		if (num[i] == '-')
			is_minus = 1;
		i++;
	}
	if (is_minus == 0)
		return (1);
	if (ft_strlen(num) < 20)
		return (1);
	else if (ft_strlen(num) > 20)
		return (0);
	else
	{
		if (check_llong_min_b(num, i) == 1)
			return (1);
		else
			return (0);
	}
}
