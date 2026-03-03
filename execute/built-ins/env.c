/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:22:55 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/24 16:37:49 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_data *data)

{
	t_env	*aux;

	if (data->cmd.cmd_exec[1])
	{
		write(2, "Error: env with no options or arguments\n", 40);
		return (127);
	}
	aux = data->b_env;
	while (aux)
	{
		if (aux->value)
			printf("%s=%s\n", aux->name, aux->value);
		aux = aux->next;
	}
	return (0);
}
