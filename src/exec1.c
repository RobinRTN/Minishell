/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:42:49 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:10:29 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_data *data)
{
	data->nbr_cmd = ft_lstsize_cmd(data->cmd);
	data->pid = ft_calloc(data->nbr_cmd, sizeof(pid_t));
	data->fdin = dup(STDIN_FILENO);
	data->fdout = dup(STDOUT_FILENO);
	if (!data->pid)
		pip_error("Error allocating data->pid\n");
}

void	handle_redirections(t_data *data)
{
	t_cmd	*cmd_cur;

	cmd_cur = data->cmd;
	if (cmd_cur == NULL)
		return ;
	exec_init(data);
	if (data->nbr_cmd == 1 && is_builtin(data->cmd))
	{
		redirections(data->cmd, data);
		exec_builtin(data->cmd, data);
	}
	else if (data->nbr_cmd == 1)
		exec_one(cmd_cur, data);
	else
		pipe_exec(data);
	reset_fd(data);
}

void	exec_one(t_cmd *cmd_cur, t_data *data)
{
	if (check_access(cmd_cur, data))
	{
		data->pid[0] = fork();
		if (data->pid[0] == -1)
			pip_error("Error, pipe failed\n");
		if (data->pid[0] == 0)
		{
			redirections(data->cmd, data);
			exec_cmd(cmd_cur, data);
		}
		wait_parent(data);
	}
}

void	exec_cmd(t_cmd *cmd, t_data *data)
{
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, data);
		close_fd(data);
	}
	else
	{
		close_fd(data);
		cleanup_heredoc(data);
		execve(cmd->cmd_path, cmd->clean_split, cmd->env);
		printf("execve failed\n");
		pip_error("Could not execute command\n");
	}
}

void	exec_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int	exit_code;

	if (is_builtin(cmd))
	{
		exec_builtin(cmd, data);
		close_fd(data);
		exit_code = data->exit_status;
		exit(exit_code);
	}
	else
	{
		cleanup_heredoc(data);
		close_fd(data);
		execve(cmd->cmd_path, cmd->clean_split, cmd->env);
		printf("execve failed\n");
		exit(126);
	}
	exit(0);
}
