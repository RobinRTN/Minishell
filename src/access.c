/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:48 by tlam              #+#    #+#             */
/*   Updated: 2024/03/07 12:19:16 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(t_cmd *cmd, t_data *data)
{
	int	file;

	if (cmd->clean_split[0] == NULL)
		return (0);
	if (is_builtin(cmd))
		return (1);
	file = check_filetype(cmd);
	if (file == 2 && ft_strstr(cmd->clean_split[0], "/"))
	{
		print_exec_error(cmd->clean_split[0], 2);
		data->exit_status = 126;
		return (0);
	}
	if (file == 0 && ft_strstr(cmd->clean_split[0], "/"))
	{
		print_exec_error(cmd->clean_split[0], 3);
		data->exit_status = 127;
		return (0);
	}
	if (command_not_found(cmd, data, file) == 0)
		return (0);
	if (permission_denied(cmd, data) == 0)
		return (0);
	return (1);
}

int	command_not_found(t_cmd *cmd, t_data *data, int file)
{
	if (access(cmd->cmd_path, F_OK) == -1 || file == 2)
	{
		data->exit_status = 127;
		print_exec_error(cmd->clean_split[0], 0);
		return (0);
	}
	if (file == 1 && access(cmd->cmd_path, X_OK) == -1)
	{
		data->exit_status = 127;
		print_exec_error(cmd->clean_split[0], 0);
		return (0);
	}
	return (1);
}

int	check_filetype(t_cmd *cmd)
{
	struct stat	path_stat;

	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(cmd->cmd_path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
		return (1);
	else if (S_ISDIR(path_stat.st_mode))
		return (2);
	else
		return (0);
}

int	permission_denied(t_cmd *cmd, t_data *data)
{
	if (access(cmd->cmd_path, X_OK) == -1)
	{
		data->exit_status = 126;
		print_exec_error(cmd->clean_split[0], 1);
		return (0);
	}
	return (1);
}
