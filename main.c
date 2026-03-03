/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:50:54 by mcabeto           #+#    #+#             */
/*   Updated: 2026/03/03 09:51:02 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_range(t_data *data, int prev_fd, int *new_prev)
{
	extrat_cmd(data);
	data->status = 0;
	if (!data->cmd.cmd_exec)
	{
		if (only_redir(data, prev_fd, new_prev))
			return (1);
	}
	else if (is_built_in(data->cmd.cmd_exec[0]))
	{
		data->status = exec_built_in_fork(data, prev_fd, new_prev);
		if (data->status)
			return (1);
	}
	else
	{
		if(exec_no_built_in(data, prev_fd, new_prev))
			return (1);
	}
	free_cmd_token(data);
	return (0);
}

int start_hdoc(t_data *data)
{
	int i;
	
	i = 0;
	while (data->token && data->token[i])
	{
		if (ft_strncmp(data->token[i],"<<", 2) == 0){
			if (create_hdoc(data, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int start_shell(t_data *data)
{	
	ft_memset(&data->cmd, 0, sizeof(data->cmd));
	if (start_hdoc(data))
		return (1);
	if (data->cmd.has_pipe)
	{
		/*data->prev_fd = -1;
		while (data->token[data->cmd.end_arr])
		{
			extract_range(data);
			data->cmd.has_pipe = 0;
			if (data->token[data->cmd.end_arr] && ft_strncmp(data->token[data->cmd.end_arr], "|",1) == 0)
				data->cmd.has_pipe = 1;
			if (exec_range(data, data->prev_fd, &data->prev_fd))
				return 1;
		}*/
		free_token(data);
		clear_hdoc(data);
		return (0);
	}
	else
	{
		extract_range(data);
		if (exec_only_cmd(data))
			return (1);
		free_cmd_token(data);
		free_token(data);
		clear_hdoc(data);
		return (0);
	}
}

void init(t_data *data)
{
	int	i;

	i = 0;
	if (data->input)
	{
		while(iswrite_space(data->input[i]))
			i++;
		if(data->input[i] == '\0')
			return ;
		data->token = split_up(data->input);
		if (data->token)
		{
			if(!check_syntax(data))
			{
				if (start_shell(data))
				{
					free_all(data);
					return ;
				}
				else
					return ;
			}
			else
				free_token(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	signals_mains();
	ft_memset(&data, 0,sizeof(data));
	extract_envp(argc, argv, envp, &data);	
	while (1)
	{
		data.input = readline("Minishell$ ");
		if (data.input == NULL)
				return (data.status);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (g_is_sigint != 0)
		{
			free_all(&data);
			data.status = g_is_sigint;
			g_is_sigint = 0;
		}
		if (data.input[0] == '\0' || data.input[0] == '\n')
			write(1,"",1);
		else
			init(&data);
		free(data.input);
	}
	return (0);
}
