/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:41:39 by sgaspar           #+#    #+#             */
/*   Updated: 2026/02/04 14:46:48 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*env_node;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(shell->exit_status));
	env_node = ft_getenv(shell->env, key);
	if (env_node && env_node->value)
		return (ft_strdup(env_node->value));
	return (ft_strdup(""));
}

char	*handle_dollar(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	start = *i;
	if (line[*i] == '?')
	{
		(*i)++;
		return (get_env_value(shell, "?"));
	}
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	key = ft_substr(line, start, *i - start);
	value = get_env_value(shell, key);
	free(key);
	return (value);
}

static void	update_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
		*sq = !(*sq);
	else if (c == '\"' && !(*sq))
		*dq = !(*dq);
}

char	*expand_str(t_shell *shell, char *line)
{
	char	*res;
	char	*tmp;
	int		i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	res = ft_strdup("");
	while (line && line[i])
	{
		update_quotes(line[i], &sq, &dq);
		if (line[i] == '$' && !sq && \
(ft_isalnum(line[i + 1]) || line[i + 1] == '_' || line[i + 1] == '?'))
		{
			tmp = handle_dollar(line, &i, shell);
			res = join_and_free(res, tmp);
			free(tmp);
		}
		else
			res = append_char(res, line[i++]);
	}
	return (res);
}

char	**expand_variable(t_shell *shell, char **matrix)
{
	int		i;
	char	*expanded;

	i = -1;
	while (matrix[++i])
	{
		if (strncmp(matrix[i], "<<", 2) == 0)
		{
			i++;
			continue ;
		}
		expanded = expand_str(shell, matrix[i]);
		free(matrix[i]);
		matrix[i] = expanded;
	}
	clean_empty_strs(matrix);
	return (matrix);
}
