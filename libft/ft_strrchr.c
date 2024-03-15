/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:18:00 by rrettien          #+#    #+#             */
/*   Updated: 2023/11/13 15:30:04 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*last;
	char	caract;

	i = 0;
	last = NULL;
	caract = (char)c;
	if (caract == '\0')
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == caract)
			last = (char *)&str[i];
		i++;
	}
	return (last);
}
