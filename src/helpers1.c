/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:28:38 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:35:10 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->full_path = NULL;
	data->path_ways = NULL;
	data->input = NULL;
	data->pr = NULL;
	data->pid = NULL;
	data->exp_input = NULL;
	data->tmp = NULL;
	data->exit_status = 0;
	data->heredocfd = -1;
	ft_memset(data->exp, 0, sizeof(data->exp));
	ft_memset(data->buf, 0, sizeof(data->buf));
	ft_memset(data->line, 0, sizeof(data->line));
	data->cmd = NULL;
	data->heredoc = NULL;
	data->envlist = NULL;
	data->i_heredoc = 0;
	data->to_exit = -1;
	data->herfd = -1;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->nbr_redir = 0;
	cmd->cmd_str = NULL;
	cmd->clean_split = NULL;
	cmd->env = NULL;
	cmd->cmd_path = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->redir = NULL;
	ft_memset(cmd->clean_cmd, '\0', sizeof(cmd->clean_cmd));
	ft_memset(cmd->buffer, '\0', sizeof(cmd->buffer));
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return ;
	}
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	pip_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

char	*ft_getenv(t_env *env, char *str)
{
	t_env	*current;

	current = ft_lstfirst_env(env);
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, str))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
