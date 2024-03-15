/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:58 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:06:46 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*result;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	result = malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[size_s1 + i] = s2[i];
	result[size_s1 + size_s2] = '\0';
	free(s2);
	return (result);
}

int	in_charset_exp(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_exp(char *s1, char *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_charset_exp(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && in_charset_exp(s1[end - 1], set))
		end--;
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 1);
	free(s1);
	return (result);
}
