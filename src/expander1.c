/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:53:01 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:23:13 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_expand(t_data *data)
{
	int		index;
	char	*final;
	char	*temp;

	index = 0;
	data->i = 0;
	data->start = 0;
	data->exp_input = ft_strdup("");
	while (data->input[data->i])
	{
		if (data->input[data->i] == '$')
		{
			make_expand_b(data, index);
			index++;
		}
		else
			data->i++;
	}
	temp = ft_substr(data->input, data->start, data->i - data->start);
	final = ft_strjoin(data->exp_input, temp);
	free(temp);
	free(data->exp_input);
	data->exp_input = final;
}

int	is_heredoc_before(char *str, t_data *data)
{
	int	j;

	j = data->i;
	while (j >= 2 && str[j - 1] == ' ')
		j--;
	if (j >= 2 && str[j - 2] == '<' && str[j - 1] == '<')
		return (1);
	return (0);
}

void	str_expand(t_data *data)
{
	int	index;

	data->i = 0;
	index = 0;
	while (data->input[data->i])
	{
		if (data->input[data->i] == 34)
			in_double_to_exp(data, &index);
		else if (data->input[data->i] == 39)
			in_simple_to_exp(data, &index);
		else
		{
			if (data->input[data->i + 1] && data->input[data->i] == '$'
				&& data->input[data->i + 1] == '?')
				data->exp[index++] = 2;
			else if (data->input[data->i] == '$' && is_var(data->input[data->i
						+ 1]) && !is_heredoc_before(data->input, data))
				data->exp[index++] = 1;
			else if (data->input[data->i] == '$')
				data->exp[index++] = -1;
		}
		data->i++;
	}
	make_expand(data);
}
