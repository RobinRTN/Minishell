/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:01:44 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 10:40:28 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_iput(char *str, int i)
{
	if (i == 0 && (str[0] == '<') && (str[1] != '<'))
		return (1);
	if (i > 0 && (*(str - 1) != '<') && (str[0] == '<') && (str[1] != '<'))
		return (1);
	return (0);
}

int	is_oput(char *str, int i)
{
	if (i == 0 && (str[0] == '>') && (str[1] != '>'))
		return (1);
	if (i > 0 && (*(str - 1) != '>') && (str[0] == '>') && (str[1] != '>'))
		return (1);
	return (0);
}

int	is_ooput(char *str)
{
	if ((str[0] == '<') && (str[1] == '<'))
		return (1);
	return (0);
}

int	is_hered(char *str)
{
	if ((str[0] == '>') && (str[1] == '>'))
		return (1);
	return (0);
}

void	in_redir(t_cmd *cur, char **str, t_data *data)
{
	char	redirect;

	if (is_iput(*str, cur->i) || is_oput(*str, cur->i))
	{
		redirect = **str;
		(*str) += 1;
		cur->i += 1;
		simple_redir_tree(cur, *str, redirect, data);
	}
	else if (is_hered(*str) || is_ooput(*str))
	{
		redirect = **str;
		(*str) += 2;
		cur->i += 2;
		double_redir_tree(cur, *str, redirect, data);
	}
	else
	{
		(*str) += 1;
		cur->i += 1;
	}
}
