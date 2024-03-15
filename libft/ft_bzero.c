/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinrettien <robinrettien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:16:17 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/09 10:05:47 by robinrettie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t len)
{
	char	*tmp_ptr;

	tmp_ptr = (char *)str;
	while (len > 0)
	{
		*tmp_ptr = 0;
		tmp_ptr++;
		len--;
	}
}
