/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:09:31 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:38:01 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static bool	ft_invalid_after_pipe(char c)
{
	return (c == '\0' || c == '>' || c == '<' || c == '&');
}

static bool	ft_triple_pipe(char *str, int i)
{
	return (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|');
}

static bool	ft_pipe_with_spaces(char *str, int i)
{
	int	j;

	if (str[i] == '|' && str[i + 1] == ' ')
	{
		j = i + 1;
		while (str[j] == ' ')
			j++;
		if (str[j] == '|')
			return (true);
	}
	return (false);
}

bool	ft_pipe_error(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
		return (true);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			i = ft_skip_quote(str, i);
		if (str[i] == '|' && ft_invalid_after_pipe(str[i + 1]))
			return (true);
		if (ft_triple_pipe(str, i))
			return (true);
		if (ft_pipe_with_spaces(str, i))
			return (true);
		i++;
	}
	return (false);
}
