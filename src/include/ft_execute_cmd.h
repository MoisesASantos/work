/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:58:32 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 14:21:59 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTE_CMD_H
# define FT_EXECUTE_CMD_H
# include "structs.h"
# include <stdbool.h>

// filedescriptor functions
void	ft_restore_fd(int original_fd[2]);
void	redirect_fd(int new_fd, int old_fd);
void	ft_save_original_fd(int original_fd[2]);
int		ft_split_len(char **arr);
// execution multi cmds functions
void	execute_external(char **argv, void *env);
int		ft_lstsize_cmd(t_cmd *lst);
int		ft_call_builtin(char **args, t_shell *shell);
int		*ft_init_child_process(t_cmd *cmd_list);
int		ft_execute_multiple_cmd(t_shell *shell);
int		execute_one_command(t_shell *shell);
int		ft_str_equal(const char *str, const char *src);
// redirect functions
void	ft_redir_heredoc(t_redirect *redir);
int		ft_redirect_in(t_cmd *cmd, t_redirect *redir);
int		ft_redirect_out(t_cmd *cmd, t_redirect *redir);
int		ft_redirect_input(t_cmd *cmd, t_redirect *redir);
int		ft_redirect_output(t_cmd *cmd, t_redirect *redir);
int		ft_handle_redirect(t_cmd *cmd);
int		ft_handle_heredoc(t_shell *shell, t_redirect *redir);
// buitld-in functions
bool	ft_is_buildin(char *str);
int		ft_cd(char **args, t_list *env);
int		ft_unset(t_list **env, char **key);
int		ft_export(t_list *env, char **key);
int		ft_env(t_list *env, char **args);
int		ft_exit(t_shell *shell, char **args);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_execute_builtin(t_shell *shell);
// pipe functions
void	ft_close_pipe(int pipefd[2]);
int		ft_handle_pipe(t_cmd *cur_cmd, int *prev_fd, int pipefd[2]);
void	ft_setup_pipes_child(int prev_fd, int pipefd[2], int has_next);
void	ft_close_parent_fds(int *prev_fd, int pipefd[2], int has_next);
// wait functions
int		wait_for_single_child(pid_t *child_pid);
int		wait_for_multiple_children(int *child_pid, int count);

#endif
