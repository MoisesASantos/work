/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:34:05 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 13:13:40 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	ft_execute_cmd_multi(t_shell *shell)
{
	if (ft_is_buildin(shell->cmd->argv[0]))
	{
		ft_execute_builtin(shell);
		exit(shell->exit_status);
	}
	execute_external(shell->cmd->argv, shell->env);
}

static void	ft_child_exec(t_shell *shell, t_cmd *cur_cmd, int prev_fd,
		int pipefd[2])
{
	ft_setup_pipes_child(prev_fd, pipefd, cur_cmd->next != NULL);
	shell->cmd = cur_cmd;
	if (ft_handle_redirect(cur_cmd) == 1)
		exit(1);
	ft_execute_cmd_multi(shell);
}

static int	ft_fork_and_exec(t_shell *shell, t_cmd *cur_cmd, int *child_pid,
		int *prev_fd)
{
	int			pipefd[2];
	static int	i;

	if (!i)
		i = 0;
	if (ft_handle_pipe(cur_cmd, prev_fd, pipefd))
		return (1);
	child_pid[i] = fork();
	if (child_pid[i] == -1)
		return (print_perror_msg("fork", NULL), 1);
	if (child_pid[i] == 0)
	{
		ft_execute_signals();
		free(child_pid);
		ft_child_exec(shell, cur_cmd, *prev_fd, pipefd);
	}
	ft_close_parent_fds(prev_fd, pipefd, cur_cmd->next != NULL);
	i++;
	if (!cur_cmd->next)
		i = 0;
	return (0);
}

int	ft_execute_multiple_cmd(t_shell *shell)
{
	t_cmd	*cur_cmd;
	int		*child_pid;
	int		count;
	int		prev_fd;
	int		exit_code;

	count = ft_lstsize_cmd(shell->cmd);
	child_pid = ft_init_child_process(shell->cmd);
	cur_cmd = shell->cmd;
	prev_fd = -1;
	ft_ignore_signals();
	while (cur_cmd)
	{
		if (ft_fork_and_exec(shell, cur_cmd, child_pid, &prev_fd))
		{
			ft_main_signals();
			return (free(child_pid), 1);
		}
		cur_cmd = cur_cmd->next;
	}
	exit_code = wait_for_multiple_children(child_pid, count);
	ft_main_signals();
	if (exit_code == 130 || exit_code == 131)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_code);
}
