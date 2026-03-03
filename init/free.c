/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:49:43 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 19:22:56 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_env(t_env *b_env)

{
	t_env	*aux;

	while (b_env)
	{
		aux = b_env;
		free(aux->name);
		free(aux->value);
		free(aux);
		b_env = b_env->next;
	}
}

void	free_array(char **array)

{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_token(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->token)
	{
		data->token = NULL;
		return ;
	}
	while (data->token[i])
	{
		free(data->token[i]);
		i++;
	}
	free(data->token);
	data->token = NULL;
}

char	*join_free(char *s1, char *s2)
{
	char	*tmp;
	if(!s2)
		tmp = ft_strjoin(s1, "");
	else
		tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

void	free_cmd_token(t_data *data)

{
	int	i;

	i = 0;
	if (!data->cmd.cmd_exec)
	{
		data->token = NULL;
		return ;
	}
	while (data->cmd.cmd_exec[i])
	{
		free(data->cmd.cmd_exec[i]);
		i++;
	}
	free(data->cmd.cmd_exec);
	data->cmd.cmd_exec = NULL;
}
