/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:45:04 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:46:20 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

bool	ft_unclosed_quote(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		return (true);
	return (false);
}

bool	ft_invalid_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			i = ft_skip_quote(str, i);
		if (str[i] == '\\' || str[i] == ';')
			return (true);
		i++;
	}
	return (false);
}

int	ft_skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	ft_syntax_error(char *str)
{
	if (ft_unclosed_quote(str))
		return (ft_error_msg("unclosed quotes token ", "\""), 1);
	if (ft_pipe_error(str))
		return (ft_error_msg("syntax error near unexpected token ", "||"), 1);
	if (ft_redirect_error(str))
		return (ft_error_msg("syntax error near unexpected token ", ">>"), 1);
	if (ft_parenthesis_error(str))
		return (ft_error_msg("syntax error near unexpected token ", ")"), 1);
	return (0);
}
