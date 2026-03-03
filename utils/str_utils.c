/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:23:47 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 18:57:08 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	step_chr(char *str, char c)

{
	int	len;

	len = 0;
	if (!str || str[len] == '\0')
		return (len);
	while (str[len] == c)
		len++;
	return (len);
}

int	find_chr(char *str, char c)
{
	int	len;

	len = 1;
	if (!str)
		return (0);
	while (str[len])
	{
		if (str[len] == c)
			return (len);
		len++;
	}
	return (len);
}

int	strchr_syntax(char *str, int c)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		if (isquote(str[i]))
			j = find_chr(str, str[i]);
		else if (str[i] == c)
			return (1);
		i += j;
		i++;
	}
	return (0);
}

void	extract_range(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd.end_arr)
		data->cmd.init_arr = data->cmd.end_arr + 1;
	while (data->token[data->cmd.init_arr + i])
	{
		if (strchr_syntax(data->token[data->cmd.init_arr + i], '|'))
			break ;
		i++;
	}
	data->cmd.end_arr = data->cmd.init_arr + i;
}

char	*str_without_redir(char **token, int start, int end)
{
	char	*tmp;

	tmp = ft_strdup("");
	if(!tmp)
		return NULL;
	while (start < end)
	{
		if ((start + 1) && (strchr_syntax(token[start], '<')
			|| strchr_syntax(token[start], '>')))
		{
			start += 2;
			continue ;
		}
		tmp = join_free(tmp, token[start]);
		if (token[start + 1])
			tmp = join_free(tmp, " ");
		start++;
	}
	return (tmp);
}
