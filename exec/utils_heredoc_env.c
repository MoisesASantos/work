/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:07:32 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:34:30 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar_hdoc(char *str, int *i)
{
	char	*aux;

	if (str[*i + 1] == '$')
	{
		aux = ft_strdup("$$");
		*i += 2;
	}
	else
	{
		if (isquote(str[*i + 1]))
			aux = ft_strdup("");
		else
			aux = ft_strdup("$");
		*i += 1;
	}
	return (aux);
}

static char	*handle_text_hdoc(char *str, int *i)
{
	int		len;
	char	*aux;

	if (isquote(str[*i]))
	{
		len = 0;
		while (str[*i + len + 1] && str[*i + len + 1] != str[*i])
			len++;
		aux = ft_substr(str, *i + 1, len);
		*i += len + 2;
	}
	else
	{
		len = 0;
		while (str[*i + len] && !isquote(str[*i + len]) && str[*i + len] != '$')
			len++;
		aux = ft_substr(str, *i, len);
		*i += len;
	}
	return (aux);
}

char	*utils_remove_quote_hdoc(char *str)
{
	int		i;
	char	*new_str;
	char	*aux;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			aux = handle_dollar_hdoc(str, &i);
		else
			aux = handle_text_hdoc(str, &i);
		new_str = join_free(new_str, aux);
		free(aux);
	}
	return (new_str);
}

static char	*expand_dollar(char *str, int *i, t_data *data)
{
	char	*name;
	char	*aux;
	int		len;

	len = len_env(str + *i + 1) + 1;
	name = ft_substr(str, *i, len);
	if (ft_strncmp(name, "$", ft_strlen(name)) == 0)
	{
		if (str[*i + 1] == '$')
		{
			aux = ft_strdup("$$");
			len++;
		}
		else
			aux = ft_strdup("$");
	}
	else if (ft_strncmp(name, "$?", ft_strlen(name) + 1) == 0)
		aux = ft_itoa(data->status);
	else
		aux = find_env_name(name + 1, data);
	free(name);
	*i += len;
	return (aux);
}

char	*hdoc_env(char *str, t_data *data)
{
	char	*new_str;
	char	*aux;
	char	*next;
	int		i;
	int		len;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			aux = expand_dollar(str, &i, data);
		if (str[i] != '$' && str[i])
		{
			len = ft_strlen(str + i);
			next = ft_strchr(str + i, '$');
			if (next)
				len = next - (str + i);
			aux = ft_substr(str, i, len);
			i += len;
		}
		new_str = join_free(new_str, aux);
		free(aux);
	}
	return (new_str);
}
