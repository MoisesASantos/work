/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_only_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:12:04 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:53:09 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_redir_cmd(t_data *data)
{
	if (to_redirect(data))
	{
		reset_fd(data);
		return (1);
	}
	reset_fd(data);
	return (0);
}

int	exec_only_cmd(t_data *data)
{
	extrat_cmd(data);
	if (!data->cmd.cmd_exec)
	{
		if (only_redir_cmd(data))
			return (1);
	}
	else if (is_built_in(data->cmd.cmd_exec[0]))
	{
		data->status = execute_if_built_exists(data);
		reset_fd(data);
		if (data->status)
			return (1);
	}
	else
	{
		if (execute_if_command_exists(data))
			return (1);
	}
	free_cmd_token(data);
	return (0);
}
