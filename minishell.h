/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:41:08 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 18:45:02 by cjeronim         ###   ########.fr       */
/*   Updated: 2026/02/25 14:10:40 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

extern int g_is_sigint;
typedef struct s_process
{
	int pipe_fd[2];
	int status;
	int pid;
}t_proc;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}t_env;

typedef struct s_heredoc
{
	int has_quote;
	char *delimiter;
	char *num;
	char *str;
	char *path;
	char *linha;
	char *linha_env;
	struct s_heredoc *next;
}t_hdoc;

typedef struct s_redir
{
	int fd;
	int in_out;
	struct s_redir *next;
}t_redir;

typedef struct s_data_redir
{
	int n_hdoc;
	t_redir *redir;
	t_hdoc *hdoc;
	t_hdoc *exec;
}t_dt_rd;

typedef struct s_cmd
{
	int has_pipe;
	int init_arr;
	int end_arr;
	char **cmd_exec;
	t_dt_rd redir;
	
}t_cmd;

typedef struct s_data
{
	int status;
	t_env *b_env;
	char *input;
	char **token;
	int orig_fd[2];
	int prev_fd;
	t_cmd cmd;
}t_data;

//init
void extract_envp(int argc, char **argv, char **envp, t_data *data);
void	save_envp(t_data *data , char *str);
void free_token(t_data *data);
void free_cmd_token(t_data *data);
void free_env(t_data *data);
void free_all(t_data *data);
void free_env_all(t_data *data);
int check_syntax(t_data *data);
void init_fd(t_data *data);
int extract_fd(t_data *data);
void reset_fd(t_data *data);
void 	free_t_env(t_env *b_env);
void print_error(t_data *data, char *str, int status);
int	found_redirect_input(t_data *data, int i);
int	found_redirect_output(t_data *data, int i);
//built-ins
int		execute_if_built_exists(t_data *data);
int		execute_echo(t_data *data);
int		execute_cd(t_data *data);
int		execute_pwd(t_data *data);
int		execute_export(t_data *data);
t_env	**order_export(t_env *data);
t_env	*found_name_env(t_env *aux, char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		execute_env(t_data *data);
int		execute_unset(t_data *data);
int		execute_exit(t_data *data);
int		parse_number(char *str, int *i, int sign, long long *res);
int		print_exit_error(char *str, int *status_code);
int		is_overflow(int sign, long long result);
int		get_sign(char *str, int *i);
int		ft_count_list(t_env *data);
int	exec_built_pipe(t_data *data);

//commands
int		execute_if_command_exists(t_data *data);
void	free_array(char **array);
char	**env_to_array(t_env *env);
char	*ft_find_command(char **broke_path, char *token);
//parse
char **split_up(char *str);
//exec
char *replace_env(char *str, t_data *data);
char *find_env_name(char *str, t_data *data);
int len_env(char *str);
int next_word(char *str);
char *double_quote_rep(char *str, int start, int len, t_data *data);
void remove_quote(t_data *data);
int check_quote(char *str);
char *utils_remove_quote(char *str);
char *utils_remove_quote_hdoc(char *str);
char *hdoc_env(char *str, t_data *data);
int exec_redir(t_data *data, int i);
int redir_hdoc(t_data *data, int i);
int create_hdoc(t_data *data, int ind);
void clear_hdoc(t_data *data);
int	exec_hdoc(t_data *data, int fd, t_hdoc *tmp);
void signals_mains(void);
void signals_ignore(void);
void signals_exec(void);
char *get_cmd_path(char *cmd, char **envp);
int is_built_in(char *str);
int to_redirect(t_data *data);
void extrat_cmd(t_data *data);
int only_redir(t_data *data, int prev_fd, int *new_prev);
int only_redir_cmd(t_data *data);
int exec_no_built_in(t_data *data, int prev_fd, int *new_prev);
int exec_only_cmd(t_data *data);
int exec_built_in_fork(t_data *data, int prev_fd, int *new_prev);
int prepare_exec(t_data *data, t_proc *tmp, int prev_fd);
void utils_pipe(t_data *data,t_proc *tmp, int prev_fd, int *new_prev);
//utils
int iswrite_space(int c);
int isquote(int c);
int ispipe(char *str, int c);
int has_shell_delimiter(int c);
int step_chr(char *str, char c);
int find_chr(char *str, char c);
int strchr_syntax(char *str , int c);
void extract_range(t_data *data);
char *join_free(char *s1, char *s2);
char *str_without_redir(char **token, int start, int end);
#endif
