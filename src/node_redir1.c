/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:15:04 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 10:33:25 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_file(char *str, int size)
{
	int		j;
	char	*file_name;

	file_name = ft_calloc((size + 1), sizeof(char));
	if (!file_name)
		pip_error_two("Failed to allocate file name\n");
	j = 0;
	while (j < size)
	{
		file_name[j] = str[j];
		j++;
	}
	file_name[j] = '\0';
	if (!file_name)
		pip_error_two(" syntax error near unexpected token `newline'\n");
	return (file_name);
}

void	simple_redir_tree(t_cmd *cur, char *str, char chev, t_data *data)
{
	if (chev == '<')
		add_redir(cur, str, 10, data);
	else if (chev == '>')
		add_redir(cur, str, 20, data);
}

void	double_redir_tree(t_cmd *cur, char *str, char chev, t_data *data)
{
	if (chev == '<')
		add_redir(cur, str, 100, data);
	else if (chev == '>')
		add_redir(cur, str, 200, data);
}

int	handle_quotes_redir(t_cmd *cur, char **str, t_data *data)
{
	if ((*str)[0] == 34)
	{
		data->dbl = !data->dbl;
		cur->i++;
		(*str)++;
		return (1);
	}
	else if ((*str)[0] == 39)
	{
		data->spl = !data->spl;
		cur->i++;
		(*str)++;
		return (1);
	}
	return (0);
}

void	redirection_lex(t_cmd *cur, char *str, int size, t_data *data)
{
	cur->i = 0;
	data->dbl = 0;
	data->spl = 0;
	while (cur->i < size && data->to_exit == -1)
	{
		if (handle_quotes_redir(cur, &str, data))
			continue ;
		if (!data->dbl && !data->spl)
			in_redir(cur, &str, data);
		else
		{
			cur->i++;
			str++;
		}
	}
}
