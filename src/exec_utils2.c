/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:00:32 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/06 14:17:52 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(t_data *data)
{
	t_cmd	*cur;

	cur = data->cmd;
	while (cur != NULL)
	{
		if (cur->pipefd[0] > 0)
			close(cur->pipefd[0]);
		if (cur->pipefd[1] > 1)
			close(cur->pipefd[1]);
		cur = cur->next;
	}
}

int	ft_strstr(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == 0)
		return (1);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	print_exec_error(char *str, int type)
{
	char	*temp;
	char	*toprint;

	temp = ft_strjoin("minishell: ", str);
	if (type == 0)
		toprint = ft_strjoin(temp, ": command not found\n");
	else if (type == 1)
		toprint = ft_strjoin(temp, ": Permission denied\n");
	else if (type == 2)
		toprint = ft_strjoin(temp, ": Is a directory\n");
	else if (type == 3)
		toprint = ft_strjoin(temp, ": No such file or directory\n");
	else
		toprint = ft_strjoin(temp, ": too many arguments\n");
	ft_putstr_fd(toprint, STDERR_FILENO);
	free(temp);
	free(toprint);
}

int	count_quotes(char *str, char set)
{
	int	i;
	int	count;
	int	result;

	result = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == set)
			count++;
		i++;
	}
	if (count % 2 == 0)
		result = count;
	else if (count % 2 == 1)
		result = count - 1;
	return (result);
}

char	*ft_allocate_echo(char *s1)
{
	int		dbl;
	int		spl;
	char	*dest;

	dbl = count_quotes(s1, '\"');
	spl = count_quotes(s1, '\'');
	dest = ft_calloc(ft_strlen(s1) - spl - dbl + 3, sizeof(char));
	if (!dest)
		return (NULL);
	return (dest);
}
