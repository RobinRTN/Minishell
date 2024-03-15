# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 09:21:44 by rrettien          #+#    #+#              #
#    Updated: 2024/03/07 12:38:05 by rrettien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OUT_DIR = ./obj
SRC = $(addprefix src/, access.c \
						builtin.c \
						builtin_functions.c \
						cd.c \
						clean_split1.c \
						clean_split2.c \
						exec1.c \
						exec2.c \
						exec_utils1.c \
						exec_utils2.c \
						exec_utils3.c \
						exit1.c \
						exit2.c \
						exit3.c \
						expander1.c \
						expander2.c \
						expander3.c \
						export1.c \
						export2.c \
						export3.c \
						first_errors.c \
						free_exit1.c \
						free_exit2.c \
						helpers1.c \
						helpers2.c \
						heredoc1.c \
						heredoc2.c \
						heredoc3.c \
						main.c \
						node_clean1.c \
						node_clean2.c \
						node_cmd1.c \
						node_cmd2.c \
						node_env.c \
						node_redir1.c \
						node_redir2.c \
						node_redir3.c \
						node_redir4.c \
						pipe_exec.c \
						prompt.c \
						redir.c \
						signals.c \
)

OBJS := $(SRC:src/%.c=$(OUT_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iincludes -Ilibft/includes
LFT = libft/libft.a

all: libft $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJS) $(LFT)
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)
	@echo "\n\033[0mDone !"
	@echo "                                                        "
	@echo "\e[38;2;255;121;198m👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽\033[0m"
	@echo "                                                        "
	@echo "\e[38;2;255;121;198m ██    ██ █ ██    █ █ █████ █   █ █████ █     █        \033[0m"
	@echo "\e[38;2;255;121;198m ███  ███ █ ███   █ █ █     █   █ █     █     █        \033[0m"
	@echo "\e[38;2;255;121;198m █ ████ █ █ █ ██  █ █ █████ █████ ████  █     █        \033[0m"
	@echo "\e[38;2;255;121;198m █  ██  █ █ █  ██ █ █     █ █   █ █     █     █        \033[0m"
	@echo "\e[38;2;255;121;198m █      █ █ █   ███ █ █████ █   █ █████ █████ █████    \033[0m"
	@echo "                                                        "
	@echo "\e[38;2;255;121;198m👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽👽\033[0m"
	@echo "                                                        "

$(OUT_DIR)/%.o: src/%.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@mkdir -p $(OUT_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJSBONUS)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME) $(NAMEBONUS)
	@make fclean -C libft/

re: fclean all

valgrind : all
	valgrind --suppressions=valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./${NAME}

.PHONY: all libft clean fclean re bonus