/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:44 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/14 15:46:15 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	space_left;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (lendst >= size)
		return (size + lensrc);
	space_left = size - lendst - 1;
	i = 0;
	while (i < space_left && src[i] != '\0')
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
