/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:30:30 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 19:11:21 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	many_parts_utils(char *str, size_t *parts, int *i, int *in_chr)
{
	if (has_shell_delimiter(str[*i]))
	{
		(*i) += step_chr(str + (*i), str[*i]);
		(*parts)++;
		(*in_chr) = 1;
	}
	else if (iswrite_space(str[*i]))
	{
		while (iswrite_space(str[*i]))
			(*i)++;
		(*in_chr) = 1;
	}
	else
	{
		(*i)++;
		if (*in_chr)
			(*parts)++;
		(*in_chr) = 0;
	}
}

static size_t	many_parts(char *str)
{
	int		i;
	int		in_chr;
	size_t	parts;

	i = 0;
	parts = 0;
	in_chr = 1;
	if (!str)
		return (parts);
	while (str[i])
	{
		if (isquote(str[i]))
		{
			i += find_chr(str + i, str[i]) + 1;
			if (in_chr)
				parts++;
			in_chr = 0;
		}
		else
			many_parts_utils(str, &parts, &i, &in_chr);
	}
	return (parts);
}

static size_t	count_word(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
	{
		if (has_shell_delimiter(str[len]) || iswrite_space(str[len]))
			break ;
		if (isquote(str[len]))
			len += find_chr(str + len, str[len]) + 1;
		else
			len++;
	}
	return (len);
}

static int	fill_arr(char **arr, char *str, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] && j < len)
	{
		while (iswrite_space(str[i]))
			i++;
		if (has_shell_delimiter(str[i]))
			count = step_chr(str + i, str[i]);
		else
			count = count_word(str + i);
		arr[j] = ft_substr(str, i, count);
		if (!arr[j])
			return (0);
		j++;
		i += count;
	}
	arr[j] = NULL;
	return (1);
}

char	**split_up(char *str)
{
	char	**arr;
	size_t	len;

	len = many_parts(str);
	arr = (char **) malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	if (!fill_arr(arr, str, len))
		return (NULL);
	return (arr);
}
