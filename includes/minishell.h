/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:22:24 by rrettien          #+#    #+#             */
/*   Updated: 2024/03/07 12:35:05 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define COLOR_VIOLET "\001\e[38;2;255;121;198m\002"
# define COLOR_GREEN "\001\e[38;2;80;255;125m\002"
# define COLOR_WHITE "\001\e[0m\002"
# define COLOR_RED "\033[38;2;255;70;100m"
# define COLOR_BLUE "\e[1;34m"
# define COLOR_RESET "\001\033[0m\002"

# define LLONG_MAX_STR "9223372036854775807"
# define LLONG_MIN_STR "-9223372036854775808"

typedef enum s_type
{
	REDIR_INPUT = 10,
	REDIR_OUTPUT = 20,
	HERE_DOC = 100,
	RED_END_OUPUT = 200
}						t_type;

typedef struct s_redir
{
	int					index;
	t_type				type;
	char				*file_name;
	char				content[3];
	char				*stopper;
	struct s_heredoc	*heredoc;
	struct s_redir		*prev;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	int					i;
	int					j;
	int					is_cmd;
	int					index;
	char				*cmd_str;
	char				clean_cmd[4096];
	char				buffer[4096];
	char				**clean_split;
	char				**env;
	int					nbr_redir;
	int					pipefd[2];
	char				*cmd_path;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	t_redir				*redir;

}						t_cmd;

typedef struct s_heredoc
{
	char				*filename;
	char				*stopper;
	int					infile;
	struct s_cmd		*cmd;
	struct s_redir		*redir;
	struct s_heredoc	*prev;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_exp
{
	char				*var;
	int					index;
	struct s_exp		*next;
}						t_exp;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					display;
	struct s_env		*prev;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	int					i;
	int					j;
	int					is_cmd;
	char				**env;
	char				*full_path;
	char				**path_ways;
	char				*input;
	char				*pr;
	int					nbr_cmd;
	pid_t				*pid;
	int					fdin;
	int					fdout;
	char				*exp_input;
	int					start;
	int					end;
	int					size;
	char				*tmp;
	int					exp[100];
	int					dbl;
	int					spl;
	int					heredocfd;
	int					exit_status;
	int					i_heredoc;
	char				buf[4096];
	char				line[4096];
	int					to_exit;
	int					herfd;
	t_cmd				*cmd;
	t_heredoc			*heredoc;
	t_env				*envlist;
}						t_data;

// Node CMD
void					add_cmd_node(t_cmd **cmd, int last, int i,
							t_data *data);
void					add_cmd(t_data *data, int i, int *last, char *str);
t_cmd					*ft_lstlast_cmd(t_cmd *cmd);
void					printf_node_cmd(t_cmd **cmd);
int						size_all_cmd(t_cmd **cmd);
int						is_empty_cmd(char *str);
void					empty_command(t_cmd **cmd, t_data *data);

// Node REDIR
char					*ft_create_file(char *str, int size);
int						count_file_size(char *str);
char					*ft_new_file(char *str, t_data *data, t_redir *current);
void					simple_redir_tree(t_cmd *cur, char *str, char chev,
							t_data *data);
void					double_redir_tree(t_cmd *cur, char *str, char chev,
							t_data *data);
void					in_redir(t_cmd *cur, char **str, t_data *data);
int						handle_quotes_redir(t_cmd *cur, char **str,
							t_data *data);
void					redirection_lex(t_cmd *cur, char *str, int size,
							t_data *data);

int						is_iput(char *str, int i);
int						is_oput(char *str, int i);
int						is_ooput(char *str);
int						is_hered(char *str);

void					add_redir_node(t_redir **redir, char *str,
							t_data *data);
void					add_redir(t_cmd *cur, char *str, int type,
							t_data *data);
t_redir					*ft_lstlast_redir(t_redir *redir);
t_redir					*ft_lstfirst_redir(t_redir *redir);

void					redir_file_error(char *str, t_data *data,
							t_redir *current);
void					ft_file_error(char *str, t_data *data,
							t_redir *current);

int						ft_first_occur(const char *haystack, const char *needle,
							size_t len, size_t min);
void					ft_extract(t_cmd *cmd, char *str, int index, int max);
void					ft_clean_whitespaces(t_cmd *cmd);
void					clean_command(t_cmd *cmd, char *str, int size,
							t_data *data);
void					inner_cmd_lex(t_cmd **cmd, t_data *data);
void					forward_char(char **strcpy, char **str);

void					full_path(t_cmd *current, t_data *data);

// Heredocs
t_heredoc				*ft_lstlast_heredoc(t_heredoc *heredoc);
t_heredoc				*ft_lstfirst_heredoc(t_heredoc *heredoc);
void					heredoc_list(t_data *data);
void					add_heredoc_node(t_data *data, t_redir *redir,
							t_cmd *cmd, int i);
void					get_heredocs(t_data *data);
int						write_to_heredoc(t_heredoc *current, t_data *data);
void					open_heredoc_for_reading(t_heredoc *current);
void					add_heredoc_to_redir(t_data *data);
void					cleanup_heredoc(t_data *data);
void					add_heredoc_node_to_data(t_data *data,
							t_heredoc *current);
void					write_heredoc_eof(t_heredoc *current, t_data *data);
void					save_fdin(t_data *data, int type);
void					end_heredoc(int fd);

// Builtins
int						is_builtin(t_cmd *cmd);
void					exec_builtin(t_cmd *cmd, t_data *data);
void					exec_pwd(t_data *data);
void					exec_echo(t_cmd *cmd, t_data *data);
int						is_jump_line(char *str);
void					exec_cd(t_cmd *cmd, t_data *data);
void					remove_env_unset(t_data *data, char *str);
void					exec_unset(t_data *data, t_cmd *cmd);
void					exec_env(t_data *data);
void					exec_exit(t_data *data, t_cmd *cmd);

// Access
int						check_access(t_cmd *cmd, t_data *data);
int						command_not_found(t_cmd *cmd, t_data *data, int file);
int						check_filetype(t_cmd *cmd);
int						permission_denied(t_cmd *cmd, t_data *data);

// Signals
void					sigint_handler(int signo);
void					sig_heredoc(int signo);
void					handle_sigquit(int signo);
void					handle_sigint(int signo);
int						sigint_heredoc_on_exit(int fd, t_data *data);

// Clean and Exit
int						split_size(char **split);
long					ft_atoi_long(const char *str);
int						check_llong_max(char *num);
int						check_llong_min_b(char *num, int i);
int						check_llong_max_b(char *num, int i);
int						check_llong_min(char *num);
int						word_alpha(char *word);
void					multiple_args(t_data *data, t_cmd *cmd);
void					exec_exit_args(t_data *data, t_cmd *cmd, int size);
void					clean_exit_msg(t_data *data, int exit_code, char *str,
							int y);
void					free_double(char **str);

int						ft_first_occur(const char *haystack, const char *needle,
							size_t len, size_t min);
void					ft_extract(t_cmd *cmd, char *str, int index, int max);
void					ft_clean_whitespaces(t_cmd *cmd);
void					inner_cmd_lex(t_cmd **cmd, t_data *data);
void					full_path(t_cmd *current, t_data *data);
void					full_path_more(t_cmd *current, t_data *data);
void					path_values(t_data *data);
int						parse_path_env_cmd(t_cmd *current, t_data *data);

// Expand
char					*ft_envname(t_data *data);
void					ft_new_exp_input(t_data *data);
void					make_expand(t_data *data);
void					make_expand_b(t_data *data, int index);
void					str_expand(t_data *data);
int						is_var(int c);
char					*ft_envalue(char *str, t_data *data);
int						quotes_parse(char *str);
int						is_full_space(char *str);
int						stopper_parse(t_data *data);
char					*ft_strtrim_exp(char *s1, char *set);
char					*ft_strjoin_free(char *s1, char *s2);
void					in_double_to_exp(t_data *data, int *index);
void					in_simple_to_exp(t_data *data, int *index);
int						is_heredoc_before(char *str, t_data *data);

// Split Clean
void					*free_tab_clean(char *split[]);
int						ft_parts_count(char *str, t_data *data);
int						to_next_q(char *str, char c);
void					write_part(const char *str, char *result, int size);
int						create_part(t_data *data, char *str, char **result);
int						write_split_clean(char **result, char *str,
							t_data *data);
char					**clean_split(t_cmd *cmd, t_data *data);
void					ft_strtrim_split(char **clean_split, t_data *data);

// ENV
void					parse_env_list(t_data *data, char **env);
t_env					*ft_lstlast_env(t_env *env);
t_env					*ft_lstfirst_env(t_env *env);
void					ft_print_env(t_env *env);

// EXPORT
void					exec_export(t_cmd *cmd, t_data *data);
void					make_env(t_data *data);
void					add_env(t_data *data, char *str);
int						check_env(char *str);
void					add_env_ndisplay(t_data *data, char *str);
void					add_env_join(t_data *data, char *str);
void					add_env_value(t_data *data, char *str);

// FREE EXIT
void					free_heredoc(t_heredoc *heredoc, t_data *data);
void					free_redir(t_redir *redir);
void					free_cmd(t_cmd *cmd);
void					free_env(t_env *env);
void					clean_after_cmd(t_data *data);
void					clean_ctrl_d(t_data *data, int exit_code);
void					clean_all(t_data *data);
void					clean_pipe(t_data *data, int exit_code);
void					clean_redir(t_data *data, char *exit_file,
							int exit_code);
void					clean_redir_bis(t_data *data, int exit_code,
							t_redir *current);

// HELPERS
void					init_data(t_data *data);
void					init_cmd(t_cmd *cmd);
void					free_double(char **str);
void					pip_error(char *str);
char					*ft_getenv(t_env *env, char *str);
void					pip_error_two(char *str);

// PROMPT
void					line_build(t_data *data);

// Exec
void					exec_init(t_data *data);
void					handle_redirections(t_data *data);
void					exec_one(t_cmd *cmd_cur, t_data *data);
void					exec_cmd(t_cmd *cmd, t_data *data);
void					exec_pipe_cmd(t_cmd *cmd, t_data *data);
void					last_pipe_cmd(t_cmd *cmd, t_data *data, int i);

// Pipes
void					pipe_exec(t_data *data);
void					pipe_child(t_cmd *cmd_cur, t_data *data, int i);
void					in_out_manager_pipe(t_data *data, t_cmd *cur, int i);
void					pipe_parent(t_data *data, t_cmd *cmd_cur, int i);
void					wait_parent(t_data *data);

// Redirections
void					redirections(t_cmd *cmd, t_data *data);
void					in_out_manager_redir(t_redir *redir, t_data *data);
void					in_out_manager_redir2(t_redir *redir, t_data *data);

// Exec Utils
int						ft_strcmp(char *s1, char *s2);
int						ft_lstsize_cmd(t_cmd *cmd);
t_cmd					*ft_lstfirst_cmd(t_cmd *cmd);
int						ft_lstsize_redir(t_redir *redir);
void					reset_fd(t_data *data);
void					close_pipe_fds(t_data *data);
int						ft_strstr(char *haystack, char *needle);
void					print_exec_error(char *str, int type);
char					*ft_strtrim_echo(char *s1, t_data *data);
char					*set_data_trim(t_data *data, char *str);
void					ft_trim_echo_loop(char *str, t_data *data, char *dest);
char					*ft_allocate_echo(char *s1);
int						count_quotes(char *str, char set);
void					print_open_error(char *str, t_data *data, int type);
void					close_fd(t_data *data);

#endif