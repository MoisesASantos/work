/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace_enc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:03:51 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:47:42 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if ((iswrite_space(str[i]) || isquote(str[i])) || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

static char	*handler_default(char *str, int start, int *adv)
{
	*adv = next_word(str + start);
	return (ft_substr(str, start, *adv));
}

static char	*handle_dollar(char *str, int start, int *advance, t_data *data)
{
	char	*name;
	char	*result;

	*advance = len_env(str + start + 1) + 1;
	name = ft_substr(str, start, *advance);
	if (ft_strncmp(name, "$", ft_strlen(name)) == 0)
	{
		if (str[start + 1] == '$')
		{
			(*advance)++;
			result = ft_strdup("$$");
		}
		else if (isquote(str[start + 1]))
			result = ft_strdup("");
		else
			result = ft_strdup("$");
	}
	else if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
		result = ft_itoa(data->status);
	else
		result = find_env_name(name + 1, data);
	free(name);
	return (result);
}

static char	*handle_special(char c)
{
	if (c == '\'')
		return (ft_strdup("'"));
	if (c == '"')
		return (ft_strdup("\""));
	return (ft_strdup(" "));
}

char	*double_quote_rep(char *str, int start, int len, t_data *data)
{
	int		i;
	int		advance;
	char	*new_str;
	char	*aux;

	i = 0;
	new_str = ft_strdup("");
	while (i < len)
	{
		if (isquote(str[start + i]) || str[start + i] == 32)
		{
			advance = 1;
			aux = handle_special(str[start + i]);
		}
		else if (str[start + i] == '$')
			aux = handle_dollar(str, start + i, &advance, data);
		else
			aux = handler_default(str, start + i, &advance);
		i += advance;
		new_str = join_free(new_str, aux);
		free(aux);
	}
	return (new_str);
}
