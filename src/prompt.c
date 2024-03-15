/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:18:10 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:18:32 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_user(t_data *data)
{
	ft_strlcat(data->line, COLOR_VIOLET, 4096);
	if (ft_getenv(data->envlist, "USER"))
		ft_strlcat(data->line, ft_getenv(data->envlist, "USER"), 4096);
	else
		ft_strlcat(data->line, "guest", 4096);
}

void	get_status(t_data *data)
{
	if (data->exit_status == 0)
		ft_strlcat(data->line, "👽 ", 4096);
	else
		ft_strlcat(data->line, "🐷 ", 4096);
}

void	get_wd(t_data *data)
{
	char	*current_dir;

	current_dir = ft_getenv(data->envlist, "PWD");
	if (current_dir)
	{
		if (ft_getenv(data->envlist, "HOME") && ft_strcmp(current_dir,
				ft_getenv(data->envlist, "HOME")) == 0)
			ft_strlcat(data->line, "~", 4096);
		else
		{
			ft_strlcat(data->line, "../", 4096);
			ft_strlcat(data->line, ft_strrchr(current_dir, '/') + 1, 4096);
		}
	}
	else
		ft_strlcat(data->line, "unknown", 4096);
}

void	line_build(t_data *data)
{
	ft_bzero(data->line, 4096);
	get_status(data);
	get_user(data);
	if (data->exit_status == 0)
		ft_strlcat(data->line, COLOR_GREEN, 4096);
	else
		ft_strlcat(data->line, COLOR_RED, 4096);
	ft_strlcat(data->line, "@minishell", 4096);
	get_wd(data);
	ft_strlcat(data->line, COLOR_WHITE, 4096);
	ft_strlcat(data->line, "$ ", 4096);
}
