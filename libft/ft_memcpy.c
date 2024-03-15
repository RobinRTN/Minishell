/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinrettien <robinrettien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:09 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/09 10:10:39 by robinrettie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*tmp_ptr_dest;
	unsigned char	*tmp_ptr_src;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	tmp_ptr_dest = (unsigned char *)dest;
	tmp_ptr_src = (unsigned char *)src;
	while (len > 0)
	{
		*tmp_ptr_dest = *tmp_ptr_src;
		tmp_ptr_dest++;
		tmp_ptr_src++;
		len--;
	}
	return (dest);
}
