/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:35:12 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:24:25 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_word(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if (isquote(str[i]) || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*find_env_name(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->b_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, ft_strlen(str) + 1) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			return (ft_strdup(""));
		}
		tmp = tmp ->next;
	}
	return (ft_strdup(""));
}

static char	*handle_quote_other(t_data *data, char *str, int i, int *len)
{
	if (str[i] == 39)
	{
		*len = find_chr(str + i, '\'') + 1;
		return (ft_substr(str, i, *len));
	}
	else if (str[i] == 34)
	{
		*len = find_chr(str + i, '\"') + 1;
		return (double_quote_rep(str, i, *len, data));
	}
	else
	{
		*len = next_word(str + i);
		return (ft_substr(str, i, *len));
	}
}

static char	*handle_dollar(char *str, int i, int *len, t_data *data)
{
	char	*name;
	char	*aux;

	*len = len_env(str + i + 1) + 1;
	name = ft_substr(str, i, *len);
	if (ft_strncmp(name, "$", ft_strlen(name)) == 0)
	{
		if (str[i + 1] == '$')
		{
			aux = ft_strdup("$$");
			(*len)++;
		}
		else if (isquote(str[i + 1]))
			aux = ft_strdup("");
		else
			aux = ft_strdup("$");
	}
	else if (ft_strncmp(name, "$?", 2) == 0)
		aux = ft_itoa(data->status);
	else
		aux = find_env_name(name + 1, data);
	free(name);
	return (aux);
}

char	*replace_env(char *str, t_data *data)
{
	char	*new_str;
	char	*aux;
	int		i;
	int		len;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			aux = handle_quote_other(data, str, i, &len);
		else if (str[i] == '\"')
			aux = handle_quote_other(data, str, i, &len);
		else if (str[i] == '$')
			aux = handle_dollar(str, i, &len, data);
		else
			aux = handle_quote_other(data, str, i, &len);
		new_str = join_free(new_str, aux);
		free(aux);
		i += len;
	}
	return (new_str);
}
