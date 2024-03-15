/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:43:06 by rrettien          #+#    #+#             */
/*   Updated: 2024/01/03 15:57:57 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*leftover[1024];
	char		*result;
	char		*buffer;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(leftover[fd]);
		buffer = NULL;
		leftover[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	result = fill_line(fd, leftover[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!result)
		return (NULL);
	leftover[fd] = set_leftover(result);
	return (result);
}

char	*fill_line(int fd, char *leftover, char *buffer)
{
	ssize_t	read_value;
	char	*tmp_str;

	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value == -1)
			return (free(leftover), NULL);
		else if (read_value == 0)
			break ;
		buffer[read_value] = '\0';
		if (!leftover)
			leftover = ft_calloc(1, 1);
		tmp_str = leftover;
		leftover = ft_strjoin(tmp_str, buffer);
		free(tmp_str);
		tmp_str = NULL;
		if (ft_strchr(leftover, '\n'))
			break ;
	}
	return (leftover);
}

char	*set_leftover(char *result)
{
	char	*left;
	int		i;

	i = 0;
	while (result[i] != '\n' && result[i] != '\0')
		i++;
	if (result[i] == 0 || result[1] == 0)
		return (NULL);
	left = ft_substr(result, i + 1, ft_strlen(result) - i);
	if (*left == 0)
	{
		free(left);
		left = NULL;
	}
	result[i + 1] = 0;
	return (left);
}
