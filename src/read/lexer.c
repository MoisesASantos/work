/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:40:21 by sgaspar           #+#    #+#             */
/*   Updated: 2026/02/04 14:42:01 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	**lexer(t_shell *shell, char *line)
{
	char	**matrix;

	matrix = ft_strip_token(line);
	free(line);
	return (expand_variable(shell, matrix));
}

char	*ft_quote_limeter(t_redirect *redir, char *line)
{
	if (ft_strchr(line, '"'))
		redir->quote_flag = 1;
	else if (ft_strchr(line, '\''))
		redir->quote_flag = 1;
	else
		redir->quote_flag = 0;
	return (ft_remove_quotes(line));
}
