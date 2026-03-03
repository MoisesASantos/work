/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:30:00 by mcabeto           #+#    #+#             */
/*   Updated: 2026/03/03 09:47:47 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handler_child_status_redir(t_data *data, int status)
{
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		if (to_redirect(data))
			exit(1);
		return (1);
	}
	else if (WIFEXITED(status))
	{
		data->status = WEXITSTATUS(status);
		if (data->status)
			return (1);
	}
	return (0);
}

int	only_redir(t_data *data, int prev_fd, int *new_prev)
{
	t_proc	tmp;

	tmp.status = 0;
	if (data->cmd.has_pipe)
		pipe(tmp.pipe_fd);
	tmp.pid = fork();
	if (tmp.pid == -1)
	{
		perror("Error: create function fork()");
		return (1);
	}
	if (tmp.pid == 0)
	{
		if (prepare_exec(data, &tmp, prev_fd))
			exit (1);
		exit(0);
	}
	signals_ignore();
	waitpid(tmp.pid, &tmp.status, 0);
	signals_mains();
	utils_pipe(data, &tmp, prev_fd, new_prev);
	return (handler_child_status_redir(data, tmp.status));
}

static int	exec_child_proc(t_data *data, t_proc *tmp, int prev_fd,
							char **array_env)
{
	t_env	*path;
	char	**broke_path;
	char	*command;

	if (prepare_exec(data, tmp, prev_fd))
		exit (1);
	if (access(data->cmd.cmd_exec[0], X_OK) == 0)
	{
		if (execve(data->cmd.cmd_exec[0], data->cmd.cmd_exec, array_env) == -1)
			exit(126);
	}
	path = found_name_env(data->b_env, "PATH");
	if (!path)
		exit(127);
	broke_path = ft_split(path->value, ':');
	if (!broke_path)
		exit(127);
	command = ft_find_command(broke_path, data->cmd.cmd_exec[0]);
	free_array(broke_path);
	if (!command)
		exit(127);
	if (execve(command, data->cmd.cmd_exec, array_env) == -1)
		exit(126);
	exit(0);
}

static int	handler_child_status_bt(t_data *data, int status)
{
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		return (1);
	}
	else if (WIFEXITED(status))
	{
		data->status = WEXITSTATUS(status);
		if (!data->status)
			return (0);
		if (data->status == 126)
			print_error(data, "Error: perror\n", 127);
		else if (data->status == 127)
		{
			ft_putstr_fd(data->cmd.cmd_exec[0], STDERR_FILENO);
			print_error(data, ": command not found\n", 127);
		}
		return (1);
	}
	return (0);
}

int	exec_no_built_in(t_data *data, int prev_fd, int *new_prev)
{
	t_proc		tmp;
	char		**array_env;

	tmp.status = 0;
	if (data->cmd.has_pipe)
		pipe(tmp.pipe_fd);
	array_env = env_to_array(data->b_env);
	tmp.pid = fork();
	if (tmp.pid == -1)
	{
		perror("Error: create function fork()");
		free_array(array_env);
		return (1);
	}
	if (tmp.pid == 0)
	{
		tmp.status = exec_child_proc(data, &tmp, prev_fd, array_env);
		exit(tmp.status);
	}
	signals_ignore();
	waitpid(tmp.pid, &tmp.status, 0);
	free_array(array_env);
	signals_mains();
	utils_pipe(data, &tmp, prev_fd, new_prev);
	return (handler_child_status_bt(data, tmp.status));
}
