/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:27:23 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 13:05:53 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	ft_execute_fork_cmd(t_shell *shell)
{
	pid_t	child_pid;
	int		exit_code;

	child_pid = fork();
	if (child_pid == -1)
	{
		print_perror_msg("fork", NULL);
		return (1);
	}
	if (child_pid == 0)
	{
		ft_execute_signals();
		if (ft_handle_redirect(shell->cmd) == 1)
			exit(1);
		execute_external(shell->cmd->argv, shell->env);
		exit(0);
	}
	ft_ignore_signals();
	exit_code = wait_for_single_child(&child_pid);
	ft_main_signals();
	if (exit_code == 130 || exit_code == 131)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_code);
}

static int	handle_redirect_only(t_shell *shell)
{
	int	original_fds[2];

	if (!shell->cmd->redirects)
		return (1);
	ft_save_original_fd(original_fds);
	if (ft_handle_redirect(shell->cmd) == 1)
	{
		ft_restore_fd(original_fds);
		return (1);
	}
	ft_restore_fd(original_fds);
	ft_close_pipe(original_fds);
	return (0);
}

static int	execute_builtin_cmd(t_shell *shell)
{
	int	original_fds[2];

	ft_save_original_fd(original_fds);
	if (ft_handle_redirect(shell->cmd) == 1)
	{
		ft_restore_fd(original_fds);
		return (1);
	}
	shell->exit_status = ft_call_builtin(shell->cmd->argv, shell);
	ft_restore_fd(original_fds);
	ft_close_pipe(original_fds);
	return (shell->exit_status);
}

int	execute_one_command(t_shell *shell)
{
	if (!shell || !shell->cmd)
		return (1);
	if (!shell->cmd->argv || !shell->cmd->argv[0])
		return (handle_redirect_only(shell));
	if (ft_is_buildin(shell->cmd->argv[0]))
		shell->exit_status = execute_builtin_cmd(shell);
	else
		shell->exit_status = ft_execute_fork_cmd(shell);
	return (shell->exit_status);
}
