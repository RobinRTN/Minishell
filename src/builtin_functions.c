/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:55:54 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:19:56 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_data *data)
{
	if (getcwd(data->buf, sizeof(data->buf)) != NULL)
	{
		ft_putstr_fd(data->buf, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		data->exit_status = 1;
		perror("getcwd");
	}
	data->exit_status = 0;
}

int	is_jump_line(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] != 'n')
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	exec_echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->clean_split[i] != NULL)
	{
		if (is_jump_line(cmd->clean_split[i]))
			newline = 0;
		else
			break ;
		i++;
	}
	while (cmd->clean_split[i] != NULL)
	{
		ft_putstr_fd(cmd->clean_split[i], STDOUT_FILENO);
		if (cmd->clean_split[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_status = 0;
}

void	exec_env(t_data *data)
{
	t_env	*cur;

	cur = data->envlist;
	while (cur)
	{
		if (cur->display == 1)
		{
			ft_putstr_fd(cur->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		cur = cur->next;
	}
	data->exit_status = 0;
}
