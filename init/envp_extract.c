/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:56:19 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 13:03:46 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	leave_program_erro(t_data *data)
{
	free_env(data);
	perror("malloc failed");
	exit(EXIT_FAILURE);
}

static int	name_exists(t_env *env, char *name, char *value)

{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if ((ft_strncmp(aux->name, name, ft_strlen(name)+1) == 0))
		{
			if(aux->value)
				free(aux->value);
			aux->value = value;
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

static int	save_envp_utils(t_env *e_new, char *str, t_data *data)
{
	char	*pos_equal;
	char	*substr;
	char	*dup;

	pos_equal = ft_strchr(str, '=');
	if (pos_equal)
	{
		substr = ft_substr(str, 0, pos_equal - str);
		if(!substr)
			return (0);
		dup = ft_strdup(pos_equal + 1);
		if(!dup)
		{
			free(substr);
			return (0);
		}
		if (name_exists(data->b_env, substr, dup))
		{
			free(substr);
			return (0);
		}
		e_new->name = substr;
		e_new->value = dup;
	}
	else
	{
		if (name_exists(data->b_env, str, NULL))
			return (0);
		e_new->name = ft_strdup(str);
		if(e_new->name)
			return (0);
		e_new->value = NULL;
	}
	e_new->next = NULL;
	return (1);
}

void	save_envp(t_data *data, char *str)
{
	t_env	*e_new;
	t_env	*aux;

	if (!str)
		return ;
	e_new = malloc(sizeof(t_env));
	if (!e_new)
		leave_program_erro(data);
	if (!save_envp_utils(e_new, str, data))
	{
		free(e_new);
		return ;
	}
	if (!data->b_env)
		data->b_env = e_new;
	else
	{
		aux = data->b_env;
		while (aux->next)
			aux = aux->next;
		aux->next = e_new;
	}
}

void	extract_envp(int argc, char **argv, char **envp, t_data *data)
{
	int	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
	{
		save_envp(data, envp[i]);
		i++;
	}
}
