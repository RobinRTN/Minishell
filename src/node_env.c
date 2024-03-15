/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:04:07 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:15:49 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

t_env	*ft_lstfirst_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->prev != NULL)
		env = env->prev;
	return (env);
}

void	ft_print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		ft_printf("key = %s\n", current->key);
		ft_printf("value = %s\n", current->value);
		ft_printf("=================\n");
		current = current->next;
	}
}

void	parse_env_list(t_data *data, char **env)
{
	t_env	*current;
	t_env	*lastnode;

	data->i = 0;
	while (env[data->i])
	{
		current = ft_calloc(2, sizeof(t_env));
		if (!current)
			pip_error("Failed to allocate the node\n");
		current->key = ft_substr(env[data->i], 0, ft_strlen(env[data->i])
				- ft_strlen(ft_strchr(env[data->i], '=')));
		current->value = ft_strdup(ft_strchr(env[data->i], '=') + 1);
		current->display = 1;
		if (data->envlist == NULL)
			data->envlist = current;
		else
		{
			lastnode = ft_lstlast_env(data->envlist);
			current->prev = lastnode;
			lastnode->next = current;
		}
		data->i++;
	}
}
