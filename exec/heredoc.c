/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <mcabeto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:50:34 by mcabeto           #+#    #+#             */
/*   Updated: 2026/02/26 14:01:42 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hdoc	*new_hdoc_node(t_data *data, char *token)
{
	t_hdoc	*tmp;

	tmp = malloc(sizeof(t_hdoc));
	if (!tmp)
	{
		perror("Error: malloc");
		return (NULL);
	}
	tmp->num = ft_itoa(++data->cmd.redir.n_hdoc);
	tmp->str = token;
	tmp->path = ft_strjoin("./hdoc", tmp->num);
	tmp->has_quote = check_quote(tmp->str);
	tmp->delimiter = utils_remove_quote_hdoc(tmp->str);
	tmp->next = NULL;
	return (tmp);
}

static void	append_hdoc(t_hdoc **head, t_hdoc *new)
{
	t_hdoc	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	create_hdoc(t_data *data, int ind)
{
	t_hdoc	*tmp;
	int		fd;

	tmp = new_hdoc_node(data, data->token[ind + 1]);
	if (!tmp)
		return (1);
	append_hdoc(&data->cmd.redir.hdoc, tmp);
	fd = open(tmp->path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
	{
		perror(tmp->path);
		data->status = 1;
		return (1);
	}
	if (exec_hdoc(data, fd, tmp))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	clear_hdoc(t_data *data)
{
	t_hdoc	*tmp;

	tmp = data->cmd.redir.hdoc;
	if (!tmp)
		return ;
	while (tmp)
	{
		data->cmd.redir.hdoc = tmp->next;
		free(tmp->num);
		unlink(tmp->path);
		free(tmp->path);
		free(tmp);
		tmp = data->cmd.redir.hdoc;
	}
	data->cmd.redir.hdoc = NULL;
}
