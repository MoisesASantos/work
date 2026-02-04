/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:09:46 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:41:26 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static bool	ft_is_redirect(char c)
{
	return (c == '>' || c == '<');
}

static bool	ft_invalid_redirect_sequence(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
		return (true);
	if ((str[i] == '>' && str[i + 1] == '<')
		|| (str[i] == '<' && str[i + 1] == '>'))
		return (true);
	return (false);
}

static bool	ft_redirect_without_target(char *str, int i)
{
	int	type_len;

	type_len = 1;
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		type_len = 2;
	i += type_len;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '&' || ft_is_redirect(str[i]))
		return (true);
	return (false);
}

bool	ft_redirect_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			i = ft_skip_quote(str, i);
		else if (ft_is_redirect(str[i]))
		{
			if (ft_invalid_redirect_sequence(str, i))
				return (true);
			if (ft_redirect_without_target(str, i))
				return (true);
		}
		i++;
	}
	return (false);
}
