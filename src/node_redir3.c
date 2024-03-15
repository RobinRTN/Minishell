/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:04:31 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 11:25:22 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir_node(t_redir **redir, char *str, t_data *data)
{
	t_redir	*current;
	t_redir	*lastnode;
	char	*temp;

	current = ft_calloc(1, sizeof(t_redir));
	if (!current)
		pip_error("Failed to allocate the node\n");
	temp = ft_new_file(str, data, current);
	if (data->to_exit == -1)
	{
		current->file_name = ft_strtrim_exp(temp, " \t\n\v\f\r");
		if (*redir == NULL)
			*redir = current;
		else
		{
			lastnode = ft_lstlast_redir(*redir);
			current->prev = lastnode;
			lastnode->next = current;
		}
	}
}

void	add_redir(t_cmd *cur, char *str, int type, t_data *data)
{
	t_redir	*lastnode;

	add_redir_node(&cur->redir, str, data);
	if (data->to_exit == -1)
	{
		lastnode = ft_lstlast_redir(cur->redir);
		lastnode->type = type;
		if (type == 10)
			ft_strlcpy(lastnode->content, "<", 2);
		else if (type == 20)
			ft_strlcpy(lastnode->content, ">", 2);
		else if (type == 100)
			ft_strlcpy(lastnode->content, "<<", 3);
		else if (type == 200)
			ft_strlcpy(lastnode->content, ">>", 3);
	}
}

t_redir	*ft_lstlast_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next != NULL)
		redir = redir->next;
	return (redir);
}

t_redir	*ft_lstfirst_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->prev != NULL)
		redir = redir->prev;
	return (redir);
}
