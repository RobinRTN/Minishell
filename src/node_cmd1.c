/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:13:47 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:24:35 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	add_cmd(t_data *data, int i, int *last, char *str)
{
	add_cmd_node(&data->cmd, *last, i, data);
	*last = i + ft_strlen(str);
}

void	add_cmd_node(t_cmd **cmd, int last, int i, t_data *data)
{
	t_cmd	*current;
	t_cmd	*lastnode;
	char	*temp;

	current = ft_calloc(1, sizeof(t_cmd));
	if (!current)
		pip_error("Failed to allocate the node\n");
	init_cmd(current);
	temp = ft_substr(data->exp_input, last, i - last);
	current->cmd_str = ft_strtrim(temp, " \t\n\v\f\r");
	current->env = NULL;
	free(temp);
	temp = NULL;
	if (*cmd == NULL)
		*cmd = current;
	else
	{
		lastnode = ft_lstlast_cmd(*cmd);
		current->prev = lastnode;
		lastnode->next = current;
	}
}
