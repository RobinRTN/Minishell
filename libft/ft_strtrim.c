/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:18:02 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/06 15:42:45 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(const char c, const char *set)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_charset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && in_charset(s1[end - 1], set))
		end--;
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}
