/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:18 by tlam              #+#    #+#             */
/*   Updated: 2024/03/06 16:58:05 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_alpha(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (!((word[i] >= '0' && word[i] <= '9') || (word[i] == '-')
				|| (word[i] == '+') || (word[i] == 34) || (word[i] == 39)))
			return (1);
		i++;
	}
	return (0);
}

void	multiple_args(t_data *data, t_cmd *cmd)
{
	if (!(word_alpha(cmd->clean_split[1])))
	{
		if (check_llong_max(cmd->clean_split[1]) == 0
			|| check_llong_min(cmd->clean_split[1]) == 0)
			clean_exit_msg(data, 2, cmd->clean_split[1], 1);
		else
		{
			data->exit_status = 1;
			ft_putstr_fd("minishell: exit:\n", 2);
			ft_putstr_fd("too many arguments\n", 2);
		}
	}
	else
		clean_exit_msg(data, 2, cmd->clean_split[1], 1);
}

void	exec_exit_args(t_data *data, t_cmd *cmd, int size)
{
	int	i;

	i = 0;
	if (size == 2)
	{
		if (word_alpha(cmd->clean_split[1]))
			clean_exit_msg(data, 2, cmd->clean_split[1], 1);
		else
		{
			if (check_llong_max(cmd->clean_split[1]) == 0
				|| check_llong_min(cmd->clean_split[1]) == 0)
				clean_exit_msg(data, 2, cmd->clean_split[1], 1);
			else
				clean_exit_msg(data, ft_atoi_long(cmd->clean_split[1]), "", 0);
		}
	}
	else
		multiple_args(data, cmd);
}

void	exec_exit(t_data *data, t_cmd *cmd)
{
	int	size;

	size = split_size(cmd->clean_split);
	if (size == 1)
		clean_exit_msg(data, 0, "", 0);
	else
		exec_exit_args(data, cmd, size);
}

void	clean_exit_msg(t_data *data, int exit_code, char *str, int y)
{
	if (y == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
	}
	clean_all(data);
	exit(exit_code);
}
