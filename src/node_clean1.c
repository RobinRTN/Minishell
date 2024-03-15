/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_clean1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:22:39 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 15:29:10 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_first_occur(const char *haystack, const char *needle, size_t len,
		size_t min)
{
	size_t	i;
	size_t	j;

	i = min;
	if (needle[0] == 0)
		return (-1);
	if (len == 0)
		return (-1);
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_extract(t_cmd *cmd, char *str, int index, int max)
{
	while (cmd->i < index && cmd->i < max && str[cmd->i] != '\0')
	{
		cmd->clean_cmd[cmd->j] = str[cmd->i];
		cmd->i++;
		cmd->j++;
	}
	cmd->clean_cmd[cmd->j] = '\0';
}

void	ft_clean_whitespaces(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*strcpy;

	i = 0;
	j = 0;
	strcpy = cmd->clean_cmd;
	while (strcpy[i])
	{
		if (strcpy[i] != ' ')
			cmd->clean_cmd[j++] = strcpy[i];
		else if (strcpy[i] == ' ' && strcpy[i + 1] != ' '
			&& strcpy[i + 1] != '\0')
			cmd->clean_cmd[j++] = ' ';
		i++;
	}
	cmd->clean_cmd[j] = '\0';
}

void	clean_command(t_cmd *cmd, char *str, int size, t_data *data)
{
	int		index;
	t_redir	*current;

	cmd->i = 0;
	cmd->j = 0;
	cmd->clean_cmd[0] = '\0';
	current = cmd->redir;
	while (current != NULL)
	{
		index = ft_first_occur(str, current->content, size, cmd->i);
		ft_extract(cmd, str, index, size);
		cmd->i += ft_strlen(current->content);
		index = ft_first_occur(str, current->file_name, size, cmd->i);
		ft_extract(cmd, str, index, size);
		cmd->i += ft_strlen(current->file_name);
		if (current->type == 100)
		{
			current->stopper = ft_strtrim_echo(current->file_name, data);
			free(current->file_name);
			current->file_name = NULL;
		}
		current = current->next;
	}
	ft_extract(cmd, str, size, size);
	ft_clean_whitespaces(cmd);
}

void	inner_cmd_lex(t_cmd **cmd, t_data *data)
{
	t_cmd	*current;
	char	*str;
	int		size;

	current = *cmd;
	while (current != NULL)
	{
		str = current->cmd_str;
		size = ft_strlen(current->cmd_str);
		redirection_lex(current, str, size, data);
		clean_command(current, str, size, data);
		current->clean_split = clean_split(current, data);
		if (!current->clean_split)
			pip_error("Failed to allocate the split\n");
		ft_strtrim_split(current->clean_split, data);
		full_path(current, data);
		current = current->next;
	}
}
