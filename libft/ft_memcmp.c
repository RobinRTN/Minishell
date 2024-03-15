/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:07 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/07 16:08:43 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t				i;
	const unsigned char	*u1;
	const unsigned char	*u2;

	u1 = (const unsigned char *)s1;
	u2 = (const unsigned char *)s2;
	i = 0;
	while (i < len)
	{
		if (u1[i] != u2[i])
			return (u1[i] - u2[i]);
		i++;
	}
	return (0);
}
