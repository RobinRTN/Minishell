/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:51:01 by rrettien          #+#    #+#             */
/*   Updated: 2024/01/03 15:58:31 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_printstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printptr(unsigned long long num)
{
	char	*result;
	char	*base;
	int		len;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (num == 0)
		return (ft_printstr("(nil)"));
	len = ft_compute_size_long(num, 16) + 2;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	result[len] = '\0';
	result[0] = '0';
	result[1] = 'x';
	while (len > 2)
	{
		result[--len] = base[num % 16];
		num /= 16;
	}
	count = ft_printstr(result);
	free(result);
	return (count);
}

int	ft_printnbr(int i)
{
	int		len;
	char	*str;

	str = ft_itoa(i);
	len = ft_printstr(str);
	free(str);
	return (len);
}
