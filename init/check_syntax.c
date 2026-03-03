/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:53:02 by mcabeto           #+#    #+#             */
/*   Updated: 2026/03/03 09:46:27 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_data *data, char *str, int status)
{
	ft_putendl_fd(str, 2);
	data->status = status;
}

static int	check_syntax_pipe(t_data *data, int i)
{
	if ((i == 0 || !data->token[i + 1]) || (ft_strlen(data->token[i]) > 1
			|| ispipe(data->token[i + 1], '|')))
	{
		print_error(data, "Error: syntax error near unexpected token \'|\'", 2);
		return (1);
	}
	else if (i > 0 && (strchr_syntax(data->token[i - 1], '>')
			|| strchr_syntax(data->token[i - 1], '<')))
	{
		print_error(data, "Error: syntax error near unexpected token \'|\'", 2);
		return (1);
	}
	return (0);
}

static int	check_syntax_redir(t_data *data, int i)
{
	if (strchr_syntax(data->token[i], '>'))
	{
		if (found_redirect_output(data, i))
			return (1);
	}
	else if (strchr_syntax(data->token[i], '<'))
	{
		if (found_redirect_input(data, i))
			return (1);
	}
	if (!data->token[i + 1])
	{
		print_error(data,
			"Error: syntax error near unexpected token \'newline\'", 2);
		return (1);
	}
	return (0);
}

static int	check_syntax_quote(t_data *data, int pos)
{
	int	i;
	int	j;

	i = 0;
	while (data->token[pos][i])
	{
		if (isquote(data->token[pos][i]))
		{
			j = find_chr(data->token[pos] + i, data->token[pos][i]);
			if (!data->token[pos][i + j])
			{
				print_error(data, "Error: missing closing quote", 2);
				return (1);
			}
			i += j;
		}
		i++;
	}
	return (0);
}

int	check_syntax(t_data *data)
{
	int	i;
	int	syntax_error;

	i = 0;
	syntax_error = 0;
	while (data->token[i])
	{
		if (strchr_syntax(data->token[i], '|'))
		{
			data->cmd.has_pipe = 1;
			syntax_error = check_syntax_pipe(data, i);
		}
		else if (strchr_syntax(data->token[i], '>')
			|| strchr_syntax(data->token[i], '<'))
			syntax_error = check_syntax_redir(data, i);
		else if (ft_strchr(data->token[i], 39) || ft_strchr(data->token[i], 34))
			syntax_error = check_syntax_quote(data, i);
		if (syntax_error)
			return (1);
		i++;
	}
	return (0);
}
