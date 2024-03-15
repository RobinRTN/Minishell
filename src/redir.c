/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:43:19 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 14:06:27 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(t_cmd *cmd, t_data *data)
{
	t_redir	*redir_cur;

	redir_cur = cmd->redir;
	cmd->env = data->env;
	signal(SIGQUIT, SIG_DFL);
	while (redir_cur != NULL)
	{
		in_out_manager_redir(redir_cur, data);
		redir_cur = redir_cur->next;
	}
}

void	in_out_manager_redir(t_redir *redir, t_data *data)
{
	int		fd;
	char	*temp;

	temp = ft_strtrim_echo(redir->file_name, data);
	fd = -1;
	if (redir->type == 10)
	{
		fd = open(temp, O_RDONLY);
		if (fd == -1)
			print_open_error(temp, data, 3);
		dup2(fd, STDIN_FILENO);
	}
	else if (redir->type == 20)
	{
		fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			print_open_error(temp, data, 1);
		dup2(fd, STDOUT_FILENO);
	}
	else if (redir->type == 100 || redir->type == 200)
		in_out_manager_redir2(redir, data);
	if (fd != -1)
		close(fd);
	free(temp);
}

void	in_out_manager_redir2(t_redir *redir, t_data *data)
{
	int		fd;
	char	*temp;

	temp = ft_strtrim_echo(redir->file_name, data);
	fd = -1;
	if (redir->type == 100)
	{
		fd = open(redir->heredoc->filename, O_RDONLY);
		if (fd == -1)
			print_open_error(redir->file_name, data, 3);
		dup2(fd, STDIN_FILENO);
	}
	else if (redir->type == 200)
	{
		fd = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			print_open_error(temp, data, 1);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	free(temp);
}
