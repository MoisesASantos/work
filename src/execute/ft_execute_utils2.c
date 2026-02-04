/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:06:28 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/17 18:49:30 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	ft_apply_redirect(t_cmd *cmd, t_redirect *redir)
{
	if (redir->type == REDIR_IN && ft_redirect_in(cmd, redir))
		return (1);
	if ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		&& ft_redirect_out(cmd, redir))
		return (1);
	return (0);
}

int	ft_handle_redirect(t_cmd *cmd)
{
	t_redirect	*redir;
	t_redirect	*last_stdin;

	redir = cmd->redirects;
	last_stdin = NULL;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			last_stdin = redir;
		if (redir->type != REDIR_HEREDOC)
		{
			if (ft_apply_redirect(cmd, redir))
				return (1);
		}
		redir = redir->next;
	}
	if (last_stdin && last_stdin->type == REDIR_HEREDOC)
		ft_redir_heredoc(last_stdin);
	return (0);
}
