/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:32:55 by sgaspar           #+#    #+#             */
/*   Updated: 2025/12/01 18:52:58 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	free_env_content(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

static int	lst_del(t_list **list, void *data)
{
	t_list	*tmp;
	t_list	*current;

	if (!list || !*list || !data)
		return (0);
	if ((*list)->content == data)
	{
		tmp = *list;
		*list = (*list)->next;
		free_env_content((t_env *)tmp->content);
		return (free(tmp), 1);
	}
	current = *list;
	while (current->next)
	{
		if (current->next->content == data)
		{
			tmp = current->next;
			current->next = tmp->next;
			free_env_content((t_env *)tmp->content);
			return (free(tmp), 1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_list **env, char **key)
{
	t_env	*info;
	int		i;

	if (!env || !*env || !key)
		return (0);
	i = -1;
	while (key[++i])
	{
		info = ft_getenv(*env, key[i]);
		if (info)
			lst_del(env, info);
	}
	return (0);
}
