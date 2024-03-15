/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:11:07 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:29:21 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredoc(t_data *data)
{
	t_heredoc	*heredoc;
	t_heredoc	*temp;

	heredoc = data->heredoc;
	while (heredoc != NULL)
	{
		temp = heredoc->next;
		if (heredoc->infile != -1)
			close(heredoc->infile);
		if (heredoc->filename)
			unlink(heredoc->filename);
		free(heredoc->filename);
		free(heredoc);
		heredoc = temp;
	}
	data->heredoc = NULL;
}

void	save_fdin(t_data *data, int type)
{
	if (type == 0)
	{
		data->heredocfd = dup(STDIN_FILENO);
	}
	if (type == 1)
	{
		dup2(data->heredocfd, STDIN_FILENO);
		if (data->heredocfd != -1)
			close(data->heredocfd);
	}
}

void	end_heredoc(int fd)
{
	if (fd != -1)
		close(fd);
}
