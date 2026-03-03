/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:13:40 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:50:54 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_quoted(char *str, int *i)
{
	int		len;
	char	*aux;
	char	quote;

	len = 0;
	quote = str[*i];
	while (str[*i + len + 1] && str[*i + len + 1] != quote)
		len++;
	aux = ft_substr(str, *i + 1, len);
	*i += len + 2;
	return (aux);
}

static char	*extract_widthout_quote(char *str, int *i)
{
	int		len;
	char	*aux;

	len = 0;
	while (str[*i + len] && !isquote(str[*i + len]))
		len++;
	aux = ft_substr(str, *i, len);
	*i += len;
	return (aux);
}

char	*utils_remove_quote(char *str)
{
	int		i;
	char	*new_str;
	char	*aux;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (isquote(str[i]))
			aux = extract_quoted(str, &i);
		else
			aux = extract_widthout_quote(str, &i);
		new_str = join_free(new_str, aux);
		free(aux);
	}
	return (new_str);
}

void	remove_quote(t_data *data)
{
	int		i;
	char	**arr;
	char	*tmp;

	i = 0;
	arr = data->cmd.cmd_exec;
	tmp = NULL;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (check_quote(arr[i]))
		{
			tmp = utils_remove_quote(arr[i]);
			free(data->cmd.cmd_exec[i]);
			data->cmd.cmd_exec[i] = tmp;
		}
		i++;
	}
}
