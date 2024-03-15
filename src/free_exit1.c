/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:47:46 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:07:59 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_heredoc *heredoc, t_data *data)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = ft_lstfirst_heredoc(heredoc);
	while (current != NULL)
	{
		next = current->next;
		if (current->filename)
			unlink(current->filename);
		if (current->filename)
		{
			free(current->filename);
			current->filename = NULL;
		}
		if (current->infile != -1)
			close(current->infile);
		free(current);
		current = next;
	}
	data->heredoc = NULL;
}

void	free_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = ft_lstfirst_redir(redir);
	while (current != NULL)
	{
		next = current->next;
		if (current->file_name)
		{
			free(current->file_name);
			current->file_name = NULL;
		}
		if (current->stopper)
		{
			free(current->stopper);
			current->stopper = NULL;
		}
		free(current);
		current = next;
	}
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
		{
			free(current->key);
			current->key = NULL;
		}
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = ft_lstfirst_cmd(cmd);
	while (current != NULL)
	{
		next = current->next;
		free_redir(current->redir);
		current->redir = NULL;
		free(current->cmd_path);
		current->cmd_path = NULL;
		free(current->cmd_str);
		current->cmd_str = NULL;
		free_double(current->clean_split);
		current->clean_split = NULL;
		free(current);
		current = next;
	}
}

void	clean_all(t_data *data)
{
	free(data->exp_input);
	data->exp_input = NULL;
	free(data->full_path);
	data->full_path = NULL;
	if (data->cmd)
		free_cmd(data->cmd);
	data->cmd = NULL;
	free_double(data->path_ways);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (data->heredoc)
		free_heredoc(data->heredoc, data);
	if (data->envlist)
		free_env(data->envlist);
	if (data->heredocfd != -1)
		close(data->heredocfd);
	reset_fd(data);
}
