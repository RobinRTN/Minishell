/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_split1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:35:15 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 08:58:42 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab_clean(char *split[])
{
	size_t	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (NULL);
}

int	ft_parts_count(char *str, t_data *data)
{
	int	parts;

	parts = 0;
	data->i = 0;
	data->spl = 0;
	data->dbl = 0;
	while (str[data->i])
	{
		if (str[data->i] == 34)
			data->dbl = !data->dbl;
		if (str[data->i] == 39)
			data->spl = !data->spl;
		if (str[data->i] != ' ' && (str[data->i + 1] == ' '
				|| str[data->i + 1] == '\0'))
		{
			if ((!data->spl && !data->dbl) || ((data->spl || data->dbl)
					&& str[data->i + 1] == '\0'))
				parts++;
		}
		data->i++;
	}
	return (parts);
}

int	create_part(t_data *data, char *str, char **result)
{
	result[data->size] = malloc((data->j + 1) * sizeof(char));
	if (!result[data->size])
		return (0);
	write_part(str + data->i, result[data->size], data->j);
	data->i += data->j;
	data->size++;
	return (1);
}

int	write_split_clean(char **result, char *str, t_data *data)
{
	data->size = 0;
	data->i = 0;
	while (str[data->i])
	{
		if (str[data->i] == ' ')
			data->i++;
		else
		{
			data->j = 0;
			while (str[data->i + data->j] != '\0')
			{
				while (str[data->i + data->j] && (str[data->i + data->j] == 34
						|| str[data->i + data->j] == 39))
					data->j += to_next_q(str + data->i + data->j, str[data->i
							+ data->j]);
				if (str[data->i + data->j] == ' ' || str[data->i
						+ data->j] == '\0')
					break ;
				data->j++;
			}
			if (!create_part(data, str, result))
				return (0);
		}
	}
	return (1);
}

char	**clean_split(t_cmd *cmd, t_data *data)
{
	char	**result;
	int		size;

	size = ft_parts_count(cmd->clean_cmd, data);
	if (size == 0)
		cmd->is_cmd = 0;
	else
		cmd->is_cmd = 1;
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[size] = NULL;
	if (!write_split_clean(result, cmd->clean_cmd, data))
		return (free_tab_clean(result), NULL);
	return (result);
}
