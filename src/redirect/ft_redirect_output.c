/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:19:58 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 11:39:55 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_redirect_output(t_cmd *cmd, t_redirect *redir)
{
	int			fd;
	int			flags;

	if (!redir)
		return (EXIT_SUCCESS);
	flags = 0;
	if (redir->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir->type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->file_name, flags, 0644);
	if (fd == -1)
	{
		if (cmd && cmd->argv && cmd->argv[0])
			print_perror_msg(cmd->argv[0], redir->file_name);
		else
			print_perror_msg(NULL, redir->file_name);
		return (EXIT_FAILURE);
	}
	redirect_fd(fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
