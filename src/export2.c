/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:28 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:24:26 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_ndisplay(t_data *data, char *str)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*last;

	tmp = ft_lstfirst_env(data->envlist);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			tmp->value = ft_strdup("");
			tmp->display = 0;
			return ;
		}
		tmp = tmp->next;
	}
	last = ft_lstlast_env(data->envlist);
	new = ft_calloc(2, sizeof(t_env));
	if (!new)
		pip_error("Failed to calloc\n");
	new->key = ft_strdup(str);
	new->value = ft_strdup("");
	new->display = 0;
	last->next = new;
	new->prev = last;
}

void	env_node_create(t_data *data, char *str, char c, int move)
{
	t_env	*new;
	t_env	*last;

	last = ft_lstlast_env(data->envlist);
	new = ft_calloc(2, sizeof(t_env));
	if (!new)
		pip_error("Failed to calloc\n");
	new->key = ft_substr(str, 0, ft_strchr(str, c) - str);
	new->value = ft_substr(str, ft_strchr(str, c) - str + move, ft_strlen(str));
	new->value = ft_strtrim_exp(new->value, "\'\"");
	new->display = 1;
	last->next = new;
	new->prev = last;
}

void	add_env_join(t_data *data, char *str)
{
	char	*key;
	char	*current_value;
	t_env	*tmp;

	tmp = data->envlist;
	key = ft_substr(str, 0, ft_strchr(str, '+') - str);
	while (tmp != NULL)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			current_value = tmp->value;
			tmp->value = ft_strjoin_free(current_value, ft_substr(str,
						ft_strchr(str, '+') - str + 2, ft_strlen(str)));
			free(current_value);
			tmp->display = 1;
			free(key);
			return ;
		}
		tmp = tmp->next;
	}
	free(key);
	env_node_create(data, str, '+', 2);
}

void	add_env_value(t_data *data, char *str)
{
	t_env	*tmp;
	char	*key;

	tmp = data->envlist;
	key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_substr(str, ft_strchr(str, '=') - str + 1,
					ft_strlen(str));
			tmp->display = 1;
			free(key);
			return ;
		}
		tmp = tmp->next;
	}
	free(key);
	env_node_create(data, str, '=', 1);
}
