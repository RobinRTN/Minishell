/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robinrettien <robinrettien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:30 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/09 10:31:31 by robinrettie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	if (cc == '\0')
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
