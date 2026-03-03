/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:29:46 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/25 13:23:56 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(t_data *data)

{
	data->orig_fd[0] = -1;
	data->orig_fd[1] = -1;
}

int	extract_fd(t_data *data)

{
	data->orig_fd[0] = dup(STDIN_FILENO);
	if (data->orig_fd[0] == -1)
		return (1);
	data->orig_fd[1] = dup(STDOUT_FILENO);
	if (data->orig_fd[1] == -1)
	{
		close(data->orig_fd[0]);
		return (1);
	}
	return (0);
}

void	reset_fd(t_data *data)

{
	if (data->orig_fd[0] != -1)
	{
		dup2(data->orig_fd[0], STDIN_FILENO);
		close(data->orig_fd[0]);
	}
	if (data->orig_fd[1] != -1)
	{
		dup2(data->orig_fd[1], STDOUT_FILENO);
		close(data->orig_fd[1]);
	}
}
