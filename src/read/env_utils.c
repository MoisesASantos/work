/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:39:32 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/19 14:39:32 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

t_env	*ft_getenv(t_list *env, char *key)
{
	t_env	*node;

	while (env)
	{
		node = (t_env *)env->content;
		if (ft_strncmp(node->key, key, ft_strlen(key) + 1) == 0)
			return (node);
		env = env->next;
	}
	return (NULL);
}

void	ft_set_env(t_list **env, char *key, char *value)
{
	t_env	*node;
	t_list	*new_node;

	node = ft_getenv(*env, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
		return ;
	}
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (free(key), free(value));
	node->key = key;
	node->value = value;
	new_node = ft_lstnew(node);
	if (!new_node)
		return (free(node->key), free(node->value), free(node));
	ft_lstadd_back(env, new_node);
}

static char	*join_env_str(char *key, char *val)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, val);
	free(tmp);
	return (res);
}

char	**ft_env_matrix(t_list *env)
{
	char	**matrix;
	t_env	*node;
	int		i;

	if (!env)
		return (NULL);
	matrix = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (env)
	{
		node = (t_env *)env->content;
		matrix[i] = join_env_str(node->key, node->value);
		env = env->next;
		i++;
	}
	return (matrix);
}
