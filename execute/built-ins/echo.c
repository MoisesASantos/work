/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:23:56 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/24 16:37:31 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_only_n(char *token)

{
	int	i;

	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (0);
		i++;
	}
	if (token[0] == '-')
		return (1);
	return (0);
}

int	execute_echo(t_data *data)

{
	int	i;

	i = 1;
	if (!data->cmd.cmd_exec[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strncmp(data->cmd.cmd_exec[1], "-n", 2) == 0
		&& ft_only_n(data->cmd.cmd_exec[1]))
		i++;
	while (data->cmd.cmd_exec[i])
	{
		ft_putstr_fd(data->cmd.cmd_exec[i], STDOUT_FILENO);
		if (data->cmd.cmd_exec[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!ft_only_n(data->cmd.cmd_exec[1]))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
