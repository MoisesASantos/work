/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:17:07 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/24 16:38:15 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validation(char *arg)

{
	int	len;

	len = ft_strlen(arg);
	if (!(ft_isalpha(arg[0]) || arg[0] == 95))
		return (0);
	if ((ft_strchr(arg, 32) && !ft_strchr(arg, '='))
		|| (ft_strchr(arg, 32) && arg[len - 1] == '='))
		return (0);
	if ((ft_strchr(arg, 32) && ft_strchr(arg, '='))
		&& (ft_strchr(arg, '=') > ft_strchr(arg, 32)))
		return (0);
	return (1);
}

static void	print_export(t_env *data)

{
	int		i;
	t_env	**array;

	i = 0;
	array = order_export(data);
	while (array[i])
	{
		if (array[i]->value == NULL)
			printf("declare -x %s\n", array[i]->name);
		else
			printf("declare -x %s=\"%s\"\n", array[i]->name, array[i]->value);
		i++;
	}
	free(array);
}

int	execute_export(t_data *data)

{
	int	i;

	i = 1;
	if (!data->cmd.cmd_exec[1])
		print_export(data->b_env);
	while (data->cmd.cmd_exec[i])
	{
		if (!validation(data->cmd.cmd_exec[i]))
		{
			ft_putstr_fd(data->cmd.cmd_exec[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(data->cmd.cmd_exec[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			data->status = 1;
			i++;
			continue ;
		}
		else
			save_envp(data, data->cmd.cmd_exec[i]);
		i++;
	}
	return (0);
}
