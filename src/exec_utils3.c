/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:01:00 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:21:03 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_data_trim(t_data *data, char *str)
{
	data->j = 0;
	data->i = 0;
	data->dbl = 0;
	data->spl = 0;
	return (ft_allocate_echo(str));
}

void	ft_trim_echo_loop(char *str, t_data *data, char *dest)
{
	while (str[data->i])
	{
		if (str[data->i] == '\"' && data->spl == 0)
			data->dbl = !data->dbl;
		else if (str[data->i] == '\'' && data->dbl == 0)
			data->spl = !data->spl;
		else if (str[data->i] == '\"' && data->dbl == 1)
		{
			data->dbl = !data->dbl;
			data->i++;
		}
		else if (str[data->i] == '\'' && data->spl == 1)
		{
			data->i++;
			data->spl = !data->spl;
		}
		else
		{
			dest[data->j] = str[data->i];
			data->j++;
		}
		data->i++;
	}
}

char	*ft_strtrim_echo(char *str, t_data *data)
{
	char	*dest;

	dest = set_data_trim(data, str);
	ft_trim_echo_loop(str, data, dest);
	dest[data->j] = '\0';
	return (dest);
}

void	print_open_error(char *str, t_data *data, int type)
{
	if (type == 3)
		print_exec_error(str, 3);
	else if (type == 1)
		print_exec_error(str, 1);
	data->exit_status = 1;
	reset_fd(data);
	close_pipe_fds(data);
	free_env(data->envlist);
	free_double(data->path_ways);
	clean_after_cmd(data);
	free(str);
	exit(1);
}

void	close_fd(t_data *data)
{
	if (data->fdin > 0)
		close(data->fdin);
	if (data->fdout > 1)
		close(data->fdout);
	data->fdin = -1;
	data->fdout = -1;
}
