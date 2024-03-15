/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:50:12 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 17:04:30 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_node_cd(t_data *data, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	tmp = ft_lstfirst_env(data->envlist);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->display = 1;
			return ;
		}
		tmp = tmp->next;
	}
	new = ft_calloc(2, sizeof(t_env));
	if (!new)
		pip_error_two("Failed to calloc\n");
	new->key = ft_strdup(key);
	new->key = ft_strdup(value);
	new->display = 1;
	tmp = ft_lstlast_env(data->envlist);
	tmp->next = new;
	new->prev = tmp;
}

void	change_pwd(t_data *data, char *former_dir)
{
	char	*curr_dir;
	char	buff[4097];

	if (!former_dir)
		env_node_cd(data, "OLDPWD", ft_getenv(data->envlist, "PWD"));
	else
		env_node_cd(data, "OLDPWD", former_dir);
	curr_dir = getcwd(buff, 4096);
	if (!curr_dir)
		return ;
	env_node_cd(data, "PWD", curr_dir);
}

void	update_pwd(char *folder, int print, t_data *data)
{
	char	*former_dir;
	char	buffer[4097];

	if (!folder)
		return ;
	former_dir = getcwd(buffer, 4096);
	if (!chdir(folder))
	{
		if (print)
			ft_printf("%s\n", folder);
		change_pwd(data, former_dir);
		data->exit_status = 0;
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(folder, 2);
		if (access(folder, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", 2);
		else if (access(folder, R_OK) == -1)
			ft_putendl_fd(": Permission denied", 2);
		else
			ft_putendl_fd(": Not a directory", 2);
		data->exit_status = 1;
	}
}

void	exec_cd(t_cmd *cmd, t_data *data)
{
	if (!cmd->clean_split[1])
		update_pwd(ft_getenv(data->envlist, "HOME"), 0, data);
	else if (cmd->clean_split[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		data->exit_status = 1;
	}
	else
	{
		if (!ft_strcmp(cmd->clean_split[1], "--")
			|| !ft_strcmp(cmd->clean_split[1], "~"))
			update_pwd(ft_getenv(data->envlist, "HOME"), 0, data);
		else if (cmd->clean_split[1][0] == '-' && !cmd->clean_split[1][1])
			update_pwd(ft_getenv(data->envlist, "OLDPWD"), 1, data);
		else
			update_pwd(cmd->clean_split[1], 0, data);
	}
}
