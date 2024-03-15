/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:10:37 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:35:40 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

void	get_heredocs(t_data *data)
{
	t_heredoc	*current;

	current = data->heredoc;
	while (current != NULL)
	{
		save_fdin(data, 0);
		if (write_to_heredoc(current, data) == 0)
		{
			save_fdin(data, 1);
			return ;
		}
		else
			open_heredoc_for_reading(current);
		current = current->next;
		save_fdin(data, 1);
	}
	add_heredoc_to_redir(data);
}

int	write_to_heredoc(t_heredoc *current, t_data *data)
{
	char	*buffer;

	data->herfd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, sig_heredoc);
	while (1)
	{
		data->i_heredoc++;
		buffer = readline("> ");
		if (g_signal_received == 2)
			return (sigint_heredoc_on_exit(data->herfd, data));
		if (buffer == NULL)
		{
			write_heredoc_eof(current, data);
			break ;
		}
		if (ft_strncmp(buffer, current->stopper,
				ft_strlen(current->stopper)) == 0)
			break ;
		ft_putstr_fd(buffer, data->herfd);
		if (buffer)
			ft_putstr_fd("\n", data->herfd);
	}
	end_heredoc(data->herfd);
	signal(SIGINT, sigint_handler);
	return (1);
}

void	write_heredoc_eof(t_heredoc *current, t_data *data)
{
	char	*temp;

	temp = ft_itoa(data->i_heredoc);
	ft_putstr_fd("minishell: warning: here_document at line ", STDERR_FILENO);
	ft_putstr_fd(temp, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(current->stopper, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	free(temp);
}

void	open_heredoc_for_reading(t_heredoc *current)
{
	current->infile = open(current->filename, O_RDWR);
	if (current->infile == -1)
		pip_error("Failed to open heredoc file for reading\n");
}

void	add_heredoc_to_redir(t_data *data)
{
	t_cmd		*cmd_cur;
	t_redir		*redir_cur;
	t_heredoc	*heredoc_cur;

	heredoc_cur = data->heredoc;
	cmd_cur = data->cmd;
	if (heredoc_cur == NULL || cmd_cur == NULL)
		return ;
	while (cmd_cur != NULL)
	{
		redir_cur = cmd_cur->redir;
		while (redir_cur != NULL)
		{
			if (redir_cur->type == 100)
			{
				redir_cur->heredoc = heredoc_cur;
				heredoc_cur = heredoc_cur->next;
			}
			else
				redir_cur->heredoc = NULL;
			redir_cur = redir_cur->next;
		}
		cmd_cur = cmd_cur->next;
	}
}
