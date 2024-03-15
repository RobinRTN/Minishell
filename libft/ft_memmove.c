/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinrettien <robinrettien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:11 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/09 10:26:33 by robinrettie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*tmp_ptr_src;
	unsigned char	*tmp_ptr_dest;
	size_t			i;

	tmp_ptr_src = (unsigned char *)src;
	tmp_ptr_dest = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	i = 0;
	if (tmp_ptr_dest > tmp_ptr_src)
	{
		while (len--)
			tmp_ptr_dest[len] = tmp_ptr_src[len];
	}
	else
	{
		while (i < len)
		{
			tmp_ptr_dest[i] = tmp_ptr_src[i];
			i++;
		}
	}
	return (dest);
}
