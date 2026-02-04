/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:34:20 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 11:43:33 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_close_pipe(int pipefd[2])
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

void	redirect_fd(int new_fd, int old_fd)
{
	if (new_fd == -1)
		return ;
	dup2(new_fd, old_fd);
	close(new_fd);
}

int	ft_redirect_in(t_cmd *cmd, t_redirect *redir)
{
	if (ft_redirect_input(cmd, redir) == 1)
		return (1);
	return (0);
}

int	ft_redirect_out(t_cmd *cmd, t_redirect *redir)
{
	if (ft_redirect_output(cmd, redir) == 1)
		return (1);
	return (0);
}

int	is_redirect_token(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, ">", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	return (0);
}
