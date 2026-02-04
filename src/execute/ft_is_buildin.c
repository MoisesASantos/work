/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:56:23 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:53:23 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_call_builtin(char **args, t_shell *shell)
{
	char	*cmd;

	cmd = args[0];
	if (ft_str_equal(cmd, "echo"))
		return (ft_echo(args));
	if (ft_str_equal(cmd, "pwd"))
		return (ft_pwd());
	if (ft_str_equal(cmd, "env"))
		return (ft_env(shell->env, args));
	if (ft_str_equal(cmd, "unset"))
		return (ft_unset(&(shell)->env, args + 1));
	if (ft_str_equal(cmd, "cd"))
		return (ft_cd(args, shell->env));
	if (ft_str_equal(cmd, "export"))
		return (ft_export(shell->env, args + 1));
	if (ft_str_equal(cmd, "exit"))
		return (ft_exit(shell, args));
	else
		return (EXIT_FAILURE);
}

int	ft_execute_builtin(t_shell *shell)
{
	shell->exit_status = ft_call_builtin(shell->cmd->argv, shell);
	exit(shell->exit_status);
}

bool	ft_is_buildin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_str_equal(cmd, "echo"))
		return (true);
	if (ft_str_equal(cmd, "pwd"))
		return (true);
	if (ft_str_equal(cmd, "env"))
		return (true);
	if (ft_str_equal(cmd, "export"))
		return (true);
	if (ft_str_equal(cmd, "unset"))
		return (true);
	if (ft_str_equal(cmd, "cd"))
		return (true);
	if (ft_str_equal(cmd, "exit"))
		return (true);
	return (false);
}
