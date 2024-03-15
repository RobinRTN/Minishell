/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:43:58 by tlam              #+#    #+#             */
/*   Updated: 2024/03/05 09:11:27 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

t_heredoc	*ft_lstlast_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return (NULL);
	while (heredoc->next != NULL)
		heredoc = heredoc->next;
	return (heredoc);
}

t_heredoc	*ft_lstfirst_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return (NULL);
	while (heredoc->prev != NULL)
		heredoc = heredoc->prev;
	return (heredoc);
}

void	heredoc_list(t_data *data)
{
	t_cmd	*cmd_cur;
	t_redir	*redir_cur;
	int		i;

	i = 0;
	cmd_cur = data->cmd;
	while (cmd_cur != NULL)
	{
		redir_cur = cmd_cur->redir;
		while (redir_cur != NULL)
		{
			if (redir_cur->type == 100)
			{
				add_heredoc_node(data, redir_cur, cmd_cur, i);
				i++;
			}
			redir_cur = redir_cur->next;
		}
		cmd_cur = cmd_cur->next;
	}
	get_heredocs(data);
}

void	add_heredoc_node(t_data *data, t_redir *redir, t_cmd *cmd, int i)
{
	t_heredoc	*current;
	char		*temp;

	current = ft_calloc(1, sizeof(t_heredoc));
	if (!current)
		pip_error("Error, could not allocate the node\n");
	temp = ft_itoa(i);
	free(current->filename);
	current->filename = ft_strjoin(".heredoc_", temp);
	free(temp);
	current->cmd = cmd;
	current->redir = redir;
	current->redir->file_name = ft_strdup(current->filename);
	current->stopper = redir->stopper;
	add_heredoc_node_to_data(data, current);
}

void	add_heredoc_node_to_data(t_data *data, t_heredoc *current)
{
	t_heredoc	*lastnode;

	if (data->heredoc == NULL)
		data->heredoc = current;
	else
	{
		lastnode = ft_lstlast_heredoc(data->heredoc);
		current->prev = lastnode;
		lastnode->next = current;
	}
}
