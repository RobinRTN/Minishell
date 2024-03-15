/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:40:18 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:34:09 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_after_cmd(t_data *data)
{
	data->to_exit = -1;
	free(data->exp_input);
	data->exp_input = NULL;
	free(data->full_path);
	data->full_path = NULL;
	save_fdin(data, 1);
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (data->heredoc != NULL)
		free_heredoc(data->heredoc, data);
}

void	clean_ctrl_d(t_data *data, int exit_code)
{
	free(data->exp_input);
	data->exp_input = NULL;
	free(data->full_path);
	data->full_path = NULL;
	free_double(data->path_ways);
	if (data->heredoc)
		free_heredoc(data->heredoc, data);
	if (ft_lstfirst_env(data->envlist))
		free_env(ft_lstfirst_env(data->envlist));
	if (data->heredocfd != -1)
		close(data->heredocfd);
	exit(exit_code);
}

void	clean_pipe(t_data *data, int exit_code)
{
	free(data->exp_input);
	data->exp_input = NULL;
	free(data->full_path);
	data->full_path = NULL;
	free_double(data->path_ways);
	if (data->heredoc)
		free_heredoc(data->heredoc, data);
	if (data->envlist)
	{
		free_env(data->envlist);
	}
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	exit(exit_code);
}

void	clean_redir(t_data *data, char *error_file, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(error_file, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(error_file);
	data->to_exit = 1;
	data->exit_status = exit_code;
}

void	clean_redir_bis(t_data *data, int exit_code, t_redir *current)
{
	free(current);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `newline'\n",
		STDERR_FILENO);
	data->to_exit = 1;
	data->exit_status = exit_code;
}
