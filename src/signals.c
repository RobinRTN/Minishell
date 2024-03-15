/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:30:05 by tlam              #+#    #+#             */
/*   Updated: 2024/03/05 09:18:51 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_received = 2;
	}
}

void	sig_heredoc(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', 1);
	g_signal_received = 2;
	close(STDIN_FILENO);
}

void	handle_sigquit(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit (core dumped)", 2);
	g_signal_received = 1;
}

void	handle_sigint(int signo)
{
	(void)signo;
	g_signal_received = 2;
}

int	sigint_heredoc_on_exit(int fd, t_data *data)
{
	signal(SIGINT, sigint_handler);
	if (fd != -1)
		close(fd);
	cleanup_heredoc(data);
	clean_after_cmd(data);
	return (0);
}
