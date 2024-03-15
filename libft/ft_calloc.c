/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:16:20 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/16 11:23:42 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*returnvalue;

	if (size == 0)
	{
		returnvalue = malloc(0);
		return (returnvalue);
	}
	if (nmemb <= 0 && size <= 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	returnvalue = malloc(nmemb * size);
	if (returnvalue == NULL || (!nmemb && !size))
		return (NULL);
	if (returnvalue)
	{
		ft_memset(returnvalue, 0, nmemb * size);
	}
	return (returnvalue);
}
