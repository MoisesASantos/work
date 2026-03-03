/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_many_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:23:46 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:56:46 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_status_bt_fork(t_data *data, int status)
{
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
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

int	exec_built_in_fork(t_data *data, int prev_fd, int *new_prev)
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
		if (exec_built_pipe(data))
			exit (1);
		else
			exit(0);
	}
	signals_ignore();
	waitpid(tmp.pid, &tmp.status, 0);
	signals_mains();
	utils_pipe(data, &tmp, prev_fd, new_prev);
	return (handle_child_status_bt_fork(data, tmp.status));
}
