/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:51:04 by rrettien          #+#    #+#             */
/*   Updated: 2024/01/03 15:58:33 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned(unsigned int num)
{
	int		count;
	char	*str;

	count = 0;
	str = ft_unsigned_itoa(num);
	count += ft_printstr(str);
	free(str);
	return (count);
}

int	ft_printhexa(unsigned int num, char x)
{
	int		count;
	int		len;
	char	*base;
	char	*result;

	if (x == 'x')
		base = "0123456789abcdef";
	else if (x == 'X')
		base = "0123456789ABCDEF";
	len = ft_compute_size(num, 16);
	if (num == 0)
		return (ft_printstr("0"));
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = base[(num % 16)];
		num /= 16;
	}
	count = ft_printstr(result);
	free(result);
	return (count);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
