/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:45:03 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/23 09:45:03 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	get_op_len(char *s)
{
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
		return (2);
	if (ft_strchr("|<>", *s))
		return (1);
	return (0);
}

static int	get_token_len(char *s)
{
	int		len;
	int		op_len;
	char	quote;

	op_len = get_op_len(s);
	if (op_len)
		return (op_len);
	len = 0;
	quote = 0;
	while (s[len])
	{
		if (!quote && (ft_isspace(s[len]) || get_op_len(s + len)))
			break ;
		if (!quote && (s[len] == '\'' || s[len] == '\"'))
			quote = s[len];
		else if (quote && s[len] == quote)
			quote = 0;
		len++;
	}
	return (len);
}

static int	count_tokens(char *line)
{
	int	count;
	int	len;

	count = 0;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (*line == '\0')
			break ;
		len = get_token_len(line);
		line += len;
		count++;
	}
	return (count);
}

static void	fill_matrix(char **matrix, char *line)
{
	int	i;
	int	len;

	i = 0;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (*line == '\0')
			break ;
		len = get_token_len(line);
		matrix[i] = ft_substr(line, 0, len);
		line += len;
		i++;
	}
	matrix[i] = NULL;
}

char	**ft_strip_token(char *line)
{
	char	**matrix;
	int		tokens;

	if (!line)
		return (NULL);
	tokens = count_tokens(line);
	matrix = ft_calloc(tokens + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	fill_matrix(matrix, line);
	return (matrix);
}
