/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:00:02 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/18 17:05:45 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_node(t_env *node)

{
	free(node->name);
	free(node->value);
	free(node);
}

static void	found_name_and_remove(t_data *data, int i)

{
	t_env	*aux;
	t_env	*tmp;

	aux = data->b_env;
	tmp = NULL;
	while (aux)
	{
		if (ft_strcmp(aux->name, data->token[i]) == 0)
		{
			if (!tmp)
			{
				data->b_env = aux->next;
				ft_remove_node(aux);
				break ;
			}
			tmp->next = aux->next;
			ft_remove_node(aux);
			break ;
		}
		tmp = aux;
		aux = aux->next;
	}
}

int	execute_unset(t_data *data)

{
	int		i;

	i = 1;
	if (data->cmd.cmd_exec[1] && data->cmd.cmd_exec[1][0] == '-')
	{
		write(2, "Error: unset with no options\n", 29);
		return (1);
	}
	while (data->cmd.cmd_exec[i])
	{
		found_name_and_remove(data, i);
		i++;
	}
	return (0);
}
