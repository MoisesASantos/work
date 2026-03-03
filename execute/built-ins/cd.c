/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:45:16 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/24 17:57:12 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*found_name_env(t_env *aux, char *s)

{
	while (aux)
	{
		if (ft_strcmp(aux->name, s) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

static void	update_value_env(t_data *data, char *value)

{
	char	*tmp;
	t_env	*aux;
	t_env	*aux_old;

	tmp = ft_strdup(value);
	aux = found_name_env(data->b_env, "PWD");
	aux_old = found_name_env(data->b_env, "OLDPWD");
	if (aux_old)
	{
		free(aux_old->value);
		aux_old->value = aux->value;
	}
	if (aux)
	{
		if (!aux_old)
			free(aux->value);
		aux->value = tmp;
	}
}

int	execute_cd(t_data *data)

{
	char	buffer[2097152];

	if (!data->cmd.cmd_exec[1] || data->cmd.cmd_exec[2])
	{
		write(2, "Error: cd with only a relative or absolute path\n", 48);
		return (1);
	}
	if (chdir(data->cmd.cmd_exec[1]) == -1)
	{
		ft_putstr_fd(data->cmd.cmd_exec[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	getcwd(buffer, sizeof(buffer));
	update_value_env(data, buffer);
	return (0);
}
