/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:00:43 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:37:45 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static bool	ft_invalid_parenthesis_combo(char *str, int i)
{
	if (str[i] == '(' && str[i + 1] == ')')
		return (true);
	if (str[i] == '(')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == ')')
			return (true);
	}
	return (false);
}

static bool	ft_unbalanced_parenthesis(int open, int close)
{
	return (open != close);
}

static bool	ft_parenthesis_count_error(char c, int *open, int *close)
{
	if (c == '(')
		(*open)++;
	else if (c == ')')
	{
		(*close)++;
		if (*close > *open)
			return (true);
	}
	return (false);
}

static bool	ft_check_parenthesis_logic(char *str)
{
	int	i;
	int	open;
	int	close;

	i = 0;
	open = 0;
	close = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			i = ft_skip_quote(str, i);
		else
		{
			if (ft_invalid_parenthesis_combo(str, i))
				return (true);
			if (ft_parenthesis_count_error(str[i], &open, &close))
				return (true);
		}
		i++;
	}
	return (ft_unbalanced_parenthesis(open, close));
}

bool	ft_parenthesis_error(char *str)
{
	if (!str || !*str)
		return (false);
	return (ft_check_parenthesis_logic(str));
}
