/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:53:57 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:23:36 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env(t_data *data)
{
	t_env	*current;

	current = data->envlist;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		if (current->display == 1)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else if (current->display == 0)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
}

void	add_env(t_data *data, char *str)
{
	data->i = 0;
	while (str[data->i] && str[data->i] != '=' && str[data->i] != '+')
		data->i++;
	if (!str[data->i])
		add_env_ndisplay(data, str);
	else if (str[data->i] == '+')
		add_env_join(data, str);
	else if (str[data->i] == '=')
		add_env_value(data, str);
	data->exit_status = 0;
}

int	check_env(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[i]) && arg[i] != '_'))
		return (0);
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	if (((i != 0 && ft_strchr(arg, '=') && !(arg[i] == '+' && arg[i
						+ 1] == '\0')) && !(arg[0] == '+' || arg[0] == '=')
			&& !(arg[i] == '+' && arg[i + 1] == '=')) || !ft_strchr(arg, '='))
		return (1);
	if (arg[i] == '+' && arg[i + 1] == '=' && arg[i + 2] == '\0')
		return (0);
	if (arg[0] == '+' && arg[1] == '=' && ft_isalpha(arg[2]))
		return (0);
	if (arg[i] == '+' && arg[i + 1] == '=' && ft_isalpha(arg[i + 2]))
		return (1);
	return (0);
}

void	exec_export(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd->clean_split[1])
		make_env(data);
	else
	{
		while (cmd->clean_split[i])
		{
			if (!check_env(cmd->clean_split[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(cmd->clean_split[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				data->exit_status = 1;
				i++;
				continue ;
			}
			add_env(data, cmd->clean_split[i]);
			i++;
		}
	}
}
