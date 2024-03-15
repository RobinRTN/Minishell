/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:43:58 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:18:26 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

void	pipe_exec(t_data *data)
{
	t_cmd	*cmd_cur;
	int		i;

	i = 0;
	cmd_cur = data->cmd;
	while (cmd_cur != NULL)
	{
		if (pipe(cmd_cur->pipefd) == -1)
		{
			close_pipe_fds(data);
			perror("pipe failed");
		}
		cmd_cur = cmd_cur->next;
	}
	cmd_cur = data->cmd;
	while (cmd_cur->next != NULL)
	{
		if (check_access(cmd_cur, data))
			pipe_child(cmd_cur, data, i);
		cmd_cur = cmd_cur->next;
		i++;
	}
	last_pipe_cmd(cmd_cur, data, i);
	close_pipe_fds(data);
	wait_parent(data);
}

void	pipe_child(t_cmd *cmd_cur, t_data *data, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		pip_error("Error, fork failed\n");
	if (data->pid[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		in_out_manager_pipe(data, cmd_cur, i);
		redirections(cmd_cur, data);
		close_pipe_fds(data);
		exec_pipe_cmd(cmd_cur, data);
	}
	else
		pipe_parent(data, cmd_cur, i);
}

void	in_out_manager_pipe(t_data *data, t_cmd *cur, int i)
{
	if (i == 0)
	{
		if (dup2(cur->pipefd[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (i == data->nbr_cmd - 1)
	{
		if (dup2(cur->prev->pipefd[0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(cur->prev->pipefd[0], STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(cur->pipefd[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
}

void	pipe_parent(t_data *data, t_cmd *cmd_cur, int i)
{
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	if (i < data->nbr_cmd - 1)
		close(cmd_cur->pipefd[1]);
}

void	wait_parent(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (i < data->nbr_cmd)
	{
		waitpid(data->pid[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		printf("\n");
		g_signal_received = 2;
	}
	signal(SIGINT, sigint_handler);
}
