/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:18:39 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:44:28 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_stdin(t_data *data, int i)
{
	int	fd;

	fd = open(data->token[i + 1], O_RDONLY);
	if (fd < 0)
	{
		perror(data->token[i + 1]);
		data->status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_stdout(t_data *data, int i)
{
	int	fd;

	fd = open(data->token[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(data->token[i + 1]);
		data->status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_stdout_append(t_data *data, int i)
{
	int	fd;

	fd = open(data->token[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(data->token[i + 1]);
		data->status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	exec_redir(t_data *data, int i)
{
	if (ft_strncmp(data->token[i], "<<", 2) == 0)
	{
		if (redir_hdoc(data, i))
			return (1);
	}
	else if (ft_strncmp(data->token[i], ">>", 2) == 0)
	{
		if (redir_stdout_append(data, i))
			return (1);
	}
	else if (ft_strncmp(data->token[i], ">", 1) == 0)
	{
		if (redir_stdout(data, i))
			return (1);
	}
	else if (ft_strncmp(data->token[i], "<", 1) == 0)
	{
		if (redir_stdin(data, i))
			return (1);
	}
	return (0);
}
