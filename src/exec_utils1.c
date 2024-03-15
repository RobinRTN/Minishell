/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:04:11 by tlam              #+#    #+#             */
/*   Updated: 2024/03/05 09:25:39 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_lstsize_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmd;
	if (cur == NULL)
		return (0);
	while (cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

t_cmd	*ft_lstfirst_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	return (cmd);
}

int	ft_lstsize_redir(t_redir *redir)
{
	t_redir	*cur;
	int		i;

	i = 0;
	cur = redir;
	if (cur == NULL)
		return (0);
	while (cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

void	reset_fd(t_data *data)
{
	if (data->fdin != -1)
	{
		dup2(data->fdin, STDIN_FILENO);
		close(data->fdin);
	}
	if (data->fdout != -1)
	{
		dup2(data->fdout, STDOUT_FILENO);
		close(data->fdout);
	}
	data->fdin = -1;
	data->fdout = -1;
}
