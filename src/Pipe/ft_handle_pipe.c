/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:38:06 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/17 18:47:12 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_setup_pipes_child(int prev_fd, int pipefd[2], int has_next)
{
	if (prev_fd != -1)
		redirect_fd(prev_fd, STDIN_FILENO);
	if (has_next)
	{
		close(pipefd[0]);
		redirect_fd(pipefd[1], STDOUT_FILENO);
	}
}

void	ft_close_parent_fds(int *prev_fd, int pipefd[2], int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

int	ft_handle_pipe(t_cmd *cur_cmd, int *prev_fd, int pipefd[2])
{
	(void)prev_fd;
	if (cur_cmd->next && pipe(pipefd) == -1)
	{
		print_perror_msg("pipe", NULL);
		return (1);
	}
	return (0);
}
