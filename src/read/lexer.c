/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:40:21 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/16 12:51:46 by sgaspar          ###   ########.fr       */
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
