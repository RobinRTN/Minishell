/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:04:03 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/05 09:04:23 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_pipe_cmd(t_cmd *cmd, t_data *data, int i)
{
	if (check_access(cmd, data))
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			perror("Error, pipe fork failed\n");
		else if (data->pid[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			in_out_manager_pipe(data, cmd, i);
			redirections(cmd, data);
			close_pipe_fds(data);
			exec_pipe_cmd(cmd, data);
			exit(0);
		}
	}
}
