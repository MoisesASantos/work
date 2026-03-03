/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:26:58 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:41:02 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *str)
{
	char	*built_in[7];
	int		i;

	i = 0;
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = "exit";
	while (i < 7)
	{
		if (ft_strncmp(str, built_in[i], ft_strlen(str) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	to_redirect(t_data *data)
{
	int	i;

	i = data->cmd.init_arr;
	data->cmd.redir.exec = data->cmd.redir.hdoc;
	while (i < data->cmd.end_arr)
	{
		if (strchr_syntax(data->token[i], '<') || strchr_syntax(data->token[i], '>'))
		{
			if (i + 1 >= data->cmd.end_arr)
    		    return (1);
			if (exec_redir(data, i))
				return (1);
		}
		i++;
	}
	data->cmd.redir.exec = NULL;
	return (0);
}

void	extrat_cmd(t_data *data)
{
	char	*tmp;
	char	*string;

	tmp = str_without_redir(data->token, data->cmd.init_arr, data->cmd.end_arr);
	if (tmp[0] != '\0')
	{
		string = replace_env(tmp, data);
		free(tmp);
		data->cmd.cmd_exec = split_up(string);
		free(string);
		remove_quote(data);
		return ;
	}
	data->cmd.cmd_exec = NULL;
	free(tmp);
}

int	prepare_exec(t_data *data, t_proc *tmp, int prev_fd)
{
	signals_exec();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (data->cmd.has_pipe)
	{
		dup2(tmp->pipe_fd[1], STDOUT_FILENO);
		close(tmp->pipe_fd[0]);
		close(tmp->pipe_fd[1]);
	}
	if (to_redirect(data))
		return (1);
	return (0);
}

void	utils_pipe(t_data *data, t_proc *tmp, int prev_fd, int *new_prev)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (data->cmd.has_pipe)
	{
		close(tmp->pipe_fd[1]);
		*new_prev = tmp->pipe_fd[0];
	}
	else
		*new_prev = -1;
}
