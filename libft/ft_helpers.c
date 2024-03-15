/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:50:55 by rrettien          #+#    #+#             */
/*   Updated: 2024/02/29 09:54:11 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_compute_size(unsigned int num, int base)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

int	ft_compute_size_long(unsigned long long num, int base)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

int	is_command(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

char	*ft_unsigned_itoa(unsigned int num)
{
	int		len;
	char	*result;

	if (num == 0)
		return (ft_strdup("0"));
	len = ft_compute_size(num, 10);
	result = malloc((len + 1) * sizeof(char));
	result[len] = '\0';
	while (len)
	{
		result[--len] = num % 10 + 48;
		num /= 10;
	}
	return (result);
}
