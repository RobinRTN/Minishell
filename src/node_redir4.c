/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redir4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:45:19 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 15:14:04 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_file_error(char *str, t_data *data, t_redir *current)
{
	int		i;
	char	*error_file;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	free(current);
	error_file = ft_substr(str, 0, 1);
	clean_redir(data, error_file, 2);
}

void	ft_file_error(char *str, t_data *data, t_redir *current)
{
	if (*str == '<' || *str == '>')
		redir_file_error(str, data, current);
}

char	*ft_new_file_b(int size, t_data *data, t_redir *current, char *str)
{
	char	*file_name;

	if (size == 0)
	{
		clean_redir_bis(data, 2, current);
		return (NULL);
	}
	file_name = ft_create_file(str, size);
	return (file_name);
}

void	forward_char(char **strcpy, char **str)
{
	while (**strcpy == ' ')
	{
		(*strcpy)++;
		(*str)++;
	}
}

char	*ft_new_file(char *str, t_data *data, t_redir *current)
{
	int		size;
	char	*strcpy;

	strcpy = str;
	size = 0;
	forward_char(&strcpy, &str);
	ft_file_error(str, data, current);
	if (data->to_exit == -1)
	{
		while (*strcpy)
		{
			while (*strcpy && (*strcpy == 34 || *strcpy == 39))
			{
				size += to_next_q(strcpy, *strcpy);
				strcpy += to_next_q(strcpy, *strcpy);
			}
			if (*strcpy == ' ' || *strcpy == '\0' || *strcpy == '<'
				|| *strcpy == '>')
				break ;
			size++;
			strcpy++;
		}
		return (ft_new_file_b(size, data, current, str));
	}
	return (NULL);
}
