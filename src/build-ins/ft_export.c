/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:16:49 by sgaspar           #+#    #+#             */
/*   Updated: 2026/02/04 11:54:46 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_box_sort(t_env **box, int tam)
{
	t_env	*tmp;
	int		i;
	int		k;

	i = -1;
	while (++i < tam)
	{
		k = -1;
		while (++k < tam)
		{
			if (ft_strcmp(box[i]->key, box[k]->key) < 0)
			{
				tmp = box[i];
				box[i] = box[k];
				box[k] = tmp;
			}
		}
	}
}

static void	ft_print_env(t_list *env, int tam)
{
	t_env	**box;
	int		i;

	box = ft_calloc(ft_lstsize(env), sizeof(t_env *));
	i = 0;
	while (env)
	{
		box[i++] = (t_env *)env->content;
		env = env->next;
	}
	ft_box_sort(box, tam);
	i = -1;
	while (++i < tam)
	{
		if (box[i]->value == NULL)
			printf("declare -x %s\n", box[i]->key);
		else if (ft_strncmp("_", box[i]->key, 1) != 0)
			printf("declare -x %s=\"%s\"\n", box[i]->key, box[i]->value);
	}
	free(box);
}

static int	ft_only_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

static int	ft_is_invalid_identity(char *str)
{
	int	i;

	i = -1;
	if (!str || !str[0])
		return (1);
	while (str[++i] && str[i] != '=')
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_') || ft_only_num(str))
			return (1);
	}
	return (0);
}

int	ft_export(t_list *env, char **args)
{
	t_env	t_env;
	int		i;

	i = -1;
	if (!args[0])
		return (ft_print_env(env, ft_lstsize(env)), 0);
	if (ft_is_invalid_identity(args[0]))
		return (print_error_msg(args[0], "not a valid identifier"), 1);
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			t_env.key = ft_substr(args[i], 0, ft_strchr(args[i], '=')
					- args[i]);
			t_env.value = ft_substr(args[i], ft_strlen(t_env.key) + 1,
					ft_strlen(args[i]));
			if (*t_env.key == '\0')
				return (print_error_msg(args[0], "not a valid identifier"), 1);
			ft_set_env(&env, t_env.key, t_env.value);
		}
		else
			ft_set_env(&env, ft_strdup(args[i]), NULL);
	}
	return (0);
}
