/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:12:50 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 15:16:56 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	size_all_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = *cmd;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	empty_command(t_cmd **cmd, t_data *data)
{
	t_cmd	*current;

	current = *cmd;
	while (current != NULL)
	{
		if (is_empty_cmd(current->cmd_str) == 1 && size_all_cmd(cmd) > 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			data->exit_status = 2;
			data->to_exit = 1;
			break ;
		}
		current = current->next;
	}
}
