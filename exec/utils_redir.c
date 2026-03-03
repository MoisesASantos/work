/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:33:15 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 13:32:47 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handler_error_hdoc(t_data *data)
{
	perror("Heredoc not found for");
	data->status = 1;
	return (1);
}

int	redir_hdoc(t_data *data, int i)
{
	t_hdoc	*aux;
	int		fd;

	aux = data->cmd.redir.exec;
	while (aux)
	{
		if (ft_strncmp(data->token[i + 1], aux->str,
				ft_strlen(aux->str) + 1) == 0)
			break ;
		aux = aux->next;
	}
	if (!aux)
		return (handler_error_hdoc(data));
	fd = open(aux->path, O_RDONLY);
	if (fd < 0)
	{
		perror(aux->path);
		data->status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	data->cmd.redir.exec = aux->next;
	return (0);
}
