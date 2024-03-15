/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:53:10 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:23:23 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_double_to_exp(t_data *data, int *index)
{
	data->i++;
	while (data->input[data->i] != 34)
	{
		if (data->input[data->i + 1] && data->input[data->i] == '$'
			&& data->input[data->i + 1] == '?')
			data->exp[(*index)++] = 2;
		else if (data->input[data->i] == '$' && is_var(data->input[data->i + 1])
			&& !is_heredoc_before(data->input, data))
			data->exp[(*index)++] = 1;
		else if (data->input[data->i] == '$')
			data->exp[(*index)++] = -1;
		data->i++;
	}
}

void	in_simple_to_exp(t_data *data, int *index)
{
	data->i++;
	while (data->input[data->i] != 39)
	{
		if (data->input[data->i] == '$')
			data->exp[(*index)++] = -1;
		data->i++;
	}
}

int	is_var(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || (c == '_'))
		return (1);
	return (0);
}

char	*ft_envalue(char *str, t_data *data)
{
	t_env	*current;

	current = data->envlist;
	while (current != NULL)
	{
		if (!ft_strcmp(str, current->key))
			break ;
		current = current->next;
	}
	if (!current || !current->value)
		return (ft_strdup(""));
	return (ft_strdup(current->value));
}

char	*ft_envname(t_data *data)
{
	int		size;
	char	*env_var;

	size = 0;
	while (data->input[data->i + size + 1] != '\0' && is_var(data->input[data->i
				+ size + 1]))
		size++;
	env_var = ft_substr(data->input, data->i + 1, size);
	return (env_var);
}
