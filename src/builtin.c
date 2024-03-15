/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:24:00 by tlam              #+#    #+#             */
/*   Updated: 2024/03/07 12:20:03 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_unset(t_data *data, char *str)
{
	t_env	*cur;
	t_env	*tmp;

	cur = data->envlist;
	tmp = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, str) == 0)
		{
			if (tmp)
				tmp->next = cur->next;
			else
				data->envlist = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			break ;
		}
		tmp = cur;
		cur = cur->next;
	}
	data->exit_status = 0;
}

void	exec_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->clean_split[1] == NULL)
		return ;
	while (cmd->clean_split[i])
	{
		remove_env_unset(data, cmd->clean_split[i]);
		i++;
	}
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->clean_split[0] == NULL)
		return (0);
	if (ft_strcmp(cmd->clean_split[0], "echo") == 0
		|| ft_strcmp(cmd->clean_split[0], "cd") == 0
		|| ft_strcmp(cmd->clean_split[0], "pwd") == 0
		|| ft_strcmp(cmd->clean_split[0], "export") == 0
		|| ft_strcmp(cmd->clean_split[0], "unset") == 0
		|| ft_strcmp(cmd->clean_split[0], "env") == 0
		|| ft_strcmp(cmd->clean_split[0], "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->clean_split[0], "echo") == 0)
		exec_echo(cmd, data);
	if (ft_strcmp(cmd->clean_split[0], "cd") == 0)
		exec_cd(cmd, data);
	if (ft_strcmp(cmd->clean_split[0], "pwd") == 0)
		exec_pwd(data);
	if (ft_strcmp(cmd->clean_split[0], "export") == 0)
		exec_export(cmd, data);
	if (ft_strcmp(cmd->clean_split[0], "unset") == 0)
		exec_unset(data, cmd);
	if (ft_strcmp(cmd->clean_split[0], "env") == 0)
		exec_env(data);
	if (ft_strcmp(cmd->clean_split[0], "exit") == 0)
		exec_exit(data, cmd);
	if (data->nbr_cmd > 1)
	{
		free_env(data->envlist);
		free_double(data->path_ways);
		clean_after_cmd(data);
	}
}
