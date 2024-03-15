/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:26:53 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:36:37 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_received;

void	cutter(t_data *data, char *str, int *last, int *i)
{
	*i = 0;
	data->spl = 0;
	data->dbl = 0;
	while (*i < data->size)
	{
		if (str[0] == 34)
			data->dbl = !data->dbl;
		else if (str[0] == 39)
			data->spl = !data->spl;
		else if (str[0] == '|' && (!data->spl && !data->dbl))
			add_cmd(data, *i, last, "|");
		str++;
		*i += 1;
	}
}

void	lexer(t_data *data)
{
	int		i;
	int		last;
	char	*str;

	i = 0;
	last = 0;
	data->cmd = NULL;
	data->heredoc = NULL;
	str_expand(data);
	data->size = ft_strlen(data->exp_input);
	str = data->exp_input;
	cutter(data, str, &last, &i);
	add_cmd_node(&data->cmd, last, i, data);
	empty_command(&data->cmd, data);
	inner_cmd_lex(&data->cmd, data);
	if (data->to_exit == -1)
	{
		heredoc_list(data);
		handle_redirections(data);
	}
	clean_after_cmd(data);
}

char	**parse_path_env(char **env)
{
	size_t	i;
	char	*sub;
	char	**path_ways;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			break ;
		i++;
	}
	if (!env[i])
	{
		pip_error("PATH not found in environment variables\n");
		return (NULL);
	}
	sub = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	path_ways = ft_split(sub, ':');
	if (!path_ways)
	{
		pip_error("Failed to split the PATH correctly\n");
		return (NULL);
	}
	free(sub);
	return (path_ways);
}

void	exec(t_data *data)
{
	g_signal_received = -1;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line_build(data);
		data->input = readline(data->line);
		if (data->input == NULL)
		{
			ft_printf("exit\n");
			clean_ctrl_d(data, data->exit_status);
		}
		add_history(data->input);
		if (stopper_parse(data) == 1)
			lexer(data);
		g_signal_received = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;

	i = 0;
	if ((!env || argc > 1) && argv)
		return (1);
	init_data(&data);
	data.env = env;
	data.envlist = NULL;
	data.path_ways = parse_path_env(env);
	parse_env_list(&data, data.env);
	exec(&data);
	rl_clear_history();
	return (0);
}
