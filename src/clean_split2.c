/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:43:33 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 08:57:35 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_next_q(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i + 1);
}

void	write_part(const char *str, char *result, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
}
