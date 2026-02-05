# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mosantos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 13:19:06 by mosantos          #+#    #+#              #
#    Updated: 2025/10/29 13:19:10 by mosantos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRC_DIR		= src
LIBFT_DIR	= lib/libft
READLINE	= -lreadline

SRC =   $(SRC_DIR)/main.c \
        $(SRC_DIR)/read/env.c \
        $(SRC_DIR)/read/env_utils.c \
        $(SRC_DIR)/read/expand.c \
        $(SRC_DIR)/read/expand_utils.c \
        $(SRC_DIR)/read/ft_parse.c \
        $(SRC_DIR)/read/ft_parse_utils.c \
        $(SRC_DIR)/read/ft_read_input.c \
        $(SRC_DIR)/read/lexer.c \
        $(SRC_DIR)/read/lexer_engine.c \
        $(SRC_DIR)/error_input/ft_pipe_error.c \
        $(SRC_DIR)/error_input/ft_redirect_error.c \
        $(SRC_DIR)/error_input/ft_parenthesis_error.c \
        $(SRC_DIR)/error_input/ft_syntax_error.c \
        $(SRC_DIR)/cleanup/ft_cleanup.c \
        $(SRC_DIR)/cleanup/ft_cleanup2.c \
        $(SRC_DIR)/build-ins/ft_cd.c \
        $(SRC_DIR)/build-ins/ft_pwd.c \
        $(SRC_DIR)/build-ins/ft_exit.c \
        $(SRC_DIR)/build-ins/ft_echo.c \
        $(SRC_DIR)/build-ins/ft_env.c \
        $(SRC_DIR)/build-ins/ft_export.c \
        $(SRC_DIR)/build-ins/ft_unset.c \
        $(SRC_DIR)/execute/ft_execute_external.c \
        $(SRC_DIR)/execute/ft_execute_utils.c \
        $(SRC_DIR)/execute/ft_execute_utils2.c \
        $(SRC_DIR)/execute/ft_is_buildin.c \
        $(SRC_DIR)/execute/ft_multiple_cmd.c \
        $(SRC_DIR)/execute/ft_one_cmd.c \
        $(SRC_DIR)/minishell/init_shell.c \
        $(SRC_DIR)/minishell/minishell.c \
        $(SRC_DIR)/minishell/ft_signals.c \
        $(SRC_DIR)/redirect/ft_redirect_input.c \
        $(SRC_DIR)/redirect/ft_redirect_output.c \
        $(SRC_DIR)/redirect/ft_redirect_utils.c \
        $(SRC_DIR)/redirect/ft_heredoc.c \
        $(SRC_DIR)/Pipe/ft_handle_pipe.c \
        $(SRC_DIR)/Pipe/ft_pipe_utils.c

OBJ	= $(SRC:.c=.o)

HEADER	=	$(SRC_DIR)/include/ft_cleanup.h \
			$(SRC_DIR)/include/ft_execute_cmd.h \
			$(SRC_DIR)/include/shell.h \
			$(SRC_DIR)/include/ft_handle_input.h \
			$(SRC_DIR)/include/structs.h

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@make  -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/libft.a $(READLINE)

$(OBJ):	$(HEADER)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
