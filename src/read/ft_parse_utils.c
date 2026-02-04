/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:37:49 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 13:54:32 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	is_pipe_token(char *token)
{
	if (!token)
		return (0);
	return (ft_strncmp(token, "|", 2) == 0);
}

void	ft_lstadd_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*aux;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		aux = *lst;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_lstadd_redir(t_redirect **lst, t_redirect *new)
{
	t_redirect	*aux;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		aux = *lst;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

static char	*ft_process_quotes(char *str, int *i, char **result, int *j)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*result)[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
	return (*result);
}

char	*ft_remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			ft_process_quotes(str, &i, &result, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
