/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:43:35 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/18 17:04:43 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(t_data *data)

{
	char	buffer[2097152];

	if (data->cmd.cmd_exec[1] && data->cmd.cmd_exec[1][0] == '-')
	{
		write(2, "Error: pwd with no options\n", 27);
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (1);
	printf("%s\n", buffer);
	return (0);
}
