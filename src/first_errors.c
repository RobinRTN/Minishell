/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:14:07 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 11:31:58 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_parse(char *str)
{
	int		i;
	char	quote;
	int		closed;

	i = -1;
	closed = 1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote = str[i];
			closed = -1;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				closed = 1;
			else if (!str[i])
				return (closed);
		}
	}
	return (closed);
}

int	is_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	stopper_parse(t_data *data)
{
	if (!(data->input) || is_full_space(data->input))
		return (0);
	if (quotes_parse(data->input) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unclosed quotes\n", 2);
		data->exit_status = 1;
		return (0);
	}
	return (1);
}
