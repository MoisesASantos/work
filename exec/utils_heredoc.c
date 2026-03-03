/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:00:33 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:30:09 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handlen_exit_child(t_data *data, int status)
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

static void	process_hdoc_line(t_data *data, t_hdoc *tmp, int fd)
{
	if (ft_strchr(tmp->linha, '$') && !tmp->has_quote)
	{
		tmp->linha_env = hdoc_env(tmp->linha, data);
		write(fd, tmp->linha_env, ft_strlen(tmp->linha_env));
		write(fd, "\n", 1);
		free(tmp->linha_env);
		tmp->linha_env = NULL;
	}
	else
	{
		write(fd, tmp->linha, ft_strlen(tmp->linha));
		write(fd, "\n", 1);
	}
	free(tmp->linha);
	tmp->linha = NULL;
}

static void	hdoc_loop(t_data *data, t_hdoc *tmp, int fd)
{
	while (1)
	{
		tmp->linha = readline("> ");
		if (!tmp->linha)
		{
			write(2, "here-document delimited by EOF (wanted '", 40);
			write(2, tmp->delimiter, ft_strlen(tmp->delimiter));
			write(2, "')\n", 3);
			exit(0);
		}
		if (tmp->linha[0] == '\0')
		{
			free(tmp->linha);
			write(fd, "\n", 1);
			continue ;
		}
		if (ft_strncmp(tmp->linha, tmp->delimiter,
				ft_strlen(tmp->linha) + 1) == 0)
		{
			free(tmp->linha);
			tmp->linha = NULL;
			exit(0);
		}
		process_hdoc_line(data, tmp, fd);
	}
}

int	exec_hdoc(t_data *data, int fd, t_hdoc *tmp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signals_exec();
		hdoc_loop(data, tmp, fd);
		exit(0);
	}
	signals_ignore();
	waitpid(pid, &status, 0);
	signals_mains();
	return (handlen_exit_child(data, status));
}
