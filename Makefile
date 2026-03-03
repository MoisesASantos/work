NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft
CLINKER = -lft -lreadline
LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a
SRC = main.c\
	init/free.c\
	init/free_extra.c\
	init/envp_extract.c\
	init/check_syntax.c\
	init/extract_fd.c\
	init/utils_check_syntax_redir.c\
	parse/split_up.c\
	exec/replace_env.c\
	exec/remove_quote.c\
	exec/redir.c\
	exec/heredoc.c\
	exec/signal.c\
	exec/exec_range.c\
	exec/exec_only_cmd.c\
	exec/exec_many_cmds.c\
	exec/utils_exec.c\
	exec/utils_replace_enc.c\
	exec/utils_redir.c\
	exec/utils_heredoc.c\
	exec/utils_heredoc_env.c\
	utils/check_utils.c\
	utils/str_utils.c\
	execute/built-ins/verify_built-in.c\
	execute/built-ins/echo.c\
	execute/built-ins/cd.c\
	execute/built-ins/pwd.c\
	execute/built-ins/export.c\
	execute/built-ins/utils_export.c\
	execute/built-ins/env.c\
	execute/built-ins/unset.c\
	execute/built-ins/exit.c\
	execute/built-ins/utils_exit.c\
	execute/commands/verify_command.c
	
OBJS = $(SRC:.c=.o)
HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) $(CLINKER) -o $(NAME)

$(OBJS): $(HEADER)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)
	
clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean
	
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
	
.PHONY: all clean fclean re
