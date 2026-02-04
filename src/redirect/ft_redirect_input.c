/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:19:10 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 11:37:57 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_redirect_input(t_cmd *cmd, t_redirect *redir)
{
	int			fd;

	fd = 0;
	if (!redir)
		return (EXIT_SUCCESS);
	if (redir->type == REDIR_IN)
		fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		if (cmd && cmd->argv && cmd->argv[0])
			print_perror_msg(cmd->argv[0], redir->file_name);
		else
			print_perror_msg(NULL, redir->file_name);
		return (EXIT_FAILURE);
	}
	redirect_fd(fd, STDIN_FILENO);
	return (EXIT_SUCCESS);
}
