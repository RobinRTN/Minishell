/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:36 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:22:05 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_exp_input(t_data *data)
{
	char	*new_input;
	char	*previous;
	char	*env_value;
	char	*temp;

	temp = ft_envname(data);
	previous = ft_substr(data->input, data->start, data->i - data->start);
	env_value = ft_envalue(temp, data);
	free(temp);
	new_input = ft_strjoin(previous, env_value);
	free(previous);
	free(env_value);
	temp = data->exp_input;
	data->exp_input = ft_strjoin(temp, new_input);
	free(temp);
	free(new_input);
	data->i++;
	while (is_var(data->input[data->i]))
		data->i++;
	data->start = data->i;
}

void	ft_new_exp_exit(t_data *data)
{
	char	*new_input;
	char	*previous;
	char	*env_value;
	char	*temp;

	previous = ft_substr(data->input, data->start, data->i - data->start);
	env_value = ft_itoa(data->exit_status);
	new_input = ft_strjoin(previous, env_value);
	free(env_value);
	free(previous);
	temp = data->exp_input;
	data->exp_input = ft_strjoin(temp, new_input);
	free(temp);
	free(new_input);
	data->i += 2;
	data->start = data->i;
}

void	make_expand_b(t_data *data, int index)
{
	if (data->exp[index] == 2)
		ft_new_exp_exit(data);
	else if (data->exp[index] == 1)
		ft_new_exp_input(data);
	else
		data->i++;
}
