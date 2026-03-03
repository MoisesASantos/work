/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:23:38 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 18:45:25 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iswrite_space(int c)

{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	isquote(int c)

{
	return (c == 34 || c == 39);
}

int	has_shell_delimiter(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ispipe(char *str, int c)

{
	int	i;

	i = 0;
	if (ft_strlen(str) > 1)
		return (0);
	if (str[i] == c)
		return (1);
	return (0);
}
