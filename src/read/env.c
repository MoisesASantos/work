/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:37:10 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/21 19:00:04 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static char	*get_env_val(char *eq_ptr)
{
	if (!eq_ptr)
		return (ft_strdup(""));
	return (ft_strdup(eq_ptr + 1));
}

t_env	*create_env_node(char *raw_str)
{
	t_env	*data;
	char	*eq_ptr;

	data = ft_calloc(1, sizeof(t_env));
	if (!data)
		return (NULL);
	eq_ptr = ft_strchr(raw_str, '=');
	if (eq_ptr)
		data->key = ft_substr(raw_str, 0, eq_ptr - raw_str);
	else
		data->key = ft_strdup(raw_str);
	data->value = get_env_val(eq_ptr);
	if (!data->key || !data->value)
	{
		if (data->key)
			free(data->key);
		if (data->value)
			free(data->value);
		return (free(data), NULL);
	}
	return (data);
}

static void	increment_shlvl(t_list **env)
{
	t_env	*node;
	int		lvl;
	char	*val_str;

	node = ft_getenv(*env, "SHLVL");
	if (node && node->value)
		lvl = ft_atoi(node->value) + 1;
	else
		lvl = 1;
	if (lvl < 0)
		lvl = 0;
	else if (lvl > 1000)
	{
		print_error_msg("warning", "shell level too high, resetting to 1");
		lvl = 1;
	}
	val_str = ft_itoa(lvl);
	ft_set_env(env, ft_strdup("SHLVL"), val_str);
}

int	load_env_2_shell(char **envp, t_shell *shell)
{
	t_env	*data;
	t_list	*node;
	int		i;

	i = -1;
	while (envp[++i])
	{
		data = create_env_node(envp[i]);
		if (!data)
			continue ;
		if (ft_strncmp(data->key, "SHELL", 6) == 0)
		{
			free(data->value);
			data->value = ft_strdup(SHELLNAME);
		}
		node = ft_lstnew(data);
		if (node)
			ft_lstadd_back(&shell->env, node);
	}
	increment_shlvl(&shell->env);
	return (1);
}
