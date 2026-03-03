/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_built-in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:47:23 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/24 16:52:09 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_if_built_exists(t_data *data)
{
	init_fd(data);
	if (extract_fd(data) || to_redirect(data))
		return (1);
	if (ft_strncmp(data->cmd.cmd_exec[0], "echo", 5) == 0)
		return (execute_echo(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "cd", 3) == 0)
		return (execute_cd(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "pwd", 4) == 0)
		return (execute_pwd(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "export", 7) == 0)
		return (execute_export(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "env", 4) == 0)
		return (execute_env(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "unset", 6) == 0)
		return (execute_unset(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "exit", 5) == 0)
		return (execute_exit(data));
	else
		return (0);
}

int	exec_built_pipe(t_data *data)
{
	if (ft_strncmp(data->cmd.cmd_exec[0], "echo", 5) == 0)
		return (execute_echo(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "cd", 3) == 0)
		return (execute_cd(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "pwd", 4) == 0)
		return (execute_pwd(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "export", 7) == 0)
		return (execute_export(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "env", 4) == 0)
		return (execute_env(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "unset", 6) == 0)
		return (execute_unset(data));
	else if (ft_strncmp(data->cmd.cmd_exec[0], "exit", 5) == 0)
		return (execute_exit(data));
	else
		return (0);
}
