/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_clean2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:31:58 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 11:18:37 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_values(t_data *data)
{
	t_env	*current;

	free_double(data->path_ways);
	current = data->envlist;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, "PATH"))
		{
			data->path_ways = ft_split(current->value, ':');
			return ;
		}
		current = current->next;
	}
	data->path_ways = NULL;
}

void	full_path(t_cmd *current, t_data *data)
{
	if (current->clean_split[0] == NULL)
		return ;
	if (!ft_strcmp(current->clean_split[0], ".")
		|| !ft_strcmp(current->clean_split[0], ".."))
	{
		current->cmd_path = ft_strdup("");
		return ;
	}
	if (access(current->clean_split[0], F_OK) == 0)
	{
		current->cmd_path = ft_strdup(current->clean_split[0]);
		return ;
	}
	full_path_more(current, data);
}

int	parse_path_env_cmd(t_cmd *current, t_data *data)
{
	size_t	j;
	char	*tmp;
	char	*full_path;

	j = 0;
	while (data->path_ways[j])
	{
		tmp = ft_strjoin(data->path_ways[j], "/");
		full_path = ft_strjoin(tmp, current->clean_split[0]);
		free(tmp);
		tmp = NULL;
		if (access(full_path, F_OK) == 0)
		{
			current->cmd_path = ft_strdup(full_path);
			free(full_path);
			return (1);
		}
		else
			free(full_path);
		j++;
	}
	return (0);
}

void	full_path_more(t_cmd *current, t_data *data)
{
	path_values(data);
	if (data->path_ways)
	{
		if (parse_path_env_cmd(current, data) == 1)
			return ;
	}
	current->cmd_path = ft_strdup("");
}

void	ft_strtrim_split(char **clean_split, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (clean_split[i])
	{
		tmp = clean_split[i];
		clean_split[i] = ft_strtrim_echo(tmp, data);
		free(tmp);
		i++;
	}
}
