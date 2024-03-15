/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:26 by rrettien          #+#    #+#             */
/*   Updated: 2023/12/05 09:25:12 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

void	*free_tab(char *split[])
{
	size_t	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (NULL);
}

static void	write_word(const char *str, char *result, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
}

static int	write_split(char **result, const char *str, char c)
{
	int	word;
	int	i;
	int	j;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j] != '\0')
				j++;
			result[word] = malloc((j + 1) * sizeof(char));
			if (!result[word])
				return (0);
			write_word(str + i, result[word], c);
			i += j;
			word++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	if (!s)
		return (NULL);
	size = word_count(s, c);
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[size] = NULL;
	if (!write_split(result, s, c))
		return (free_tab(result), NULL);
	return (result);
}
