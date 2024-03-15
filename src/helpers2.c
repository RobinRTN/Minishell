/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:27:56 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:08:28 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pip_error_two(char *str)
{
	ft_putstr_fd("minishell: exit: `", 2);
	ft_putstr_fd(str, STDERR_FILENO);
	exit(2);
}
