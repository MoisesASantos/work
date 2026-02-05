/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:06:29 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 14:06:04 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_create_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	(*cmd)->argv = NULL;
	(*cmd)->redirects = NULL;
	(*cmd)->next = NULL;
}

int	ft_count_args(char **tokens, int *index)
{
	int	count;
	int	i;

	if (!tokens)
		return (0);
	count = 0;
	i = *index;
	while (tokens[i] && !is_pipe_token(tokens[i]))
	{
		if (is_redirect_token(tokens[i]))
		{
			i += 2;
			continue ;
		}
		i++;
		count++;
	}
	return (count);
}

static int	ft_store_redirect(t_cmd *cmd_node, char **tokens, int *index)
{
	t_redirect	*redir;
	char		*type_token;

	redir = ft_calloc(1, sizeof(t_redirect));
	type_token = tokens[*index];
	if (ft_strncmp(type_token, ">", 1) == 0 && type_token[1] == '\0')
		redir->type = REDIR_OUT;
	else if (ft_strncmp(type_token, ">>", 2) == 0)
		redir->type = REDIR_APPEND;
	else if (ft_strncmp(type_token, "<", 1) == 0 && type_token[1] == '\0')
		redir->type = REDIR_IN;
	else if (ft_strncmp(type_token, "<<", 2) == 0)
		redir->type = REDIR_HEREDOC;
	if (!tokens[*index + 1])
		return (free(redir), (*index)++, 0);
	if (redir->type == REDIR_HEREDOC)
		redir->limeter = ft_quote_limeter(redir, tokens[*index + 1]);
	else
		redir->file_name = ft_remove_quotes(tokens[*index + 1]);
	redir->heredoc_fd = -1;
	redir->next = NULL;
	ft_lstadd_redir(&cmd_node->redirects, redir);
	*index += 2;
	return (1);
}

t_cmd	*ft_get_node(char **tokens, t_cmd **cmd_list, int *index)
{
	t_cmd	*cmd_node;
	int		count;
	int		j;

	j = -1;
	count = ft_count_args(tokens, index);
	ft_create_cmd(&cmd_node);
	cmd_node->argv = malloc(sizeof(char *) * (count + 1));
	while (tokens[*index] && !is_pipe_token(tokens[*index]))
	{
		if (is_redirect_token(tokens[*index]))
		{
			if (!ft_store_redirect(cmd_node, tokens, index))
				return (ft_lstclean_cmd(&cmd_node, ft_free_split), NULL);
		}
		else
			cmd_node->argv[++j] = ft_remove_quotes(tokens[(*index)++]);
	}
	cmd_node->argv[++j] = NULL;
	ft_lstadd_cmd(cmd_list, cmd_node);
	if (tokens[*index] && is_pipe_token(tokens[*index]))
		(*index)++;
	return (cmd_node);
}

int	ft_parse(char **tokens, t_cmd **cmd_list)
{
	t_cmd	*cmd_node;
	int		i;

	if (!tokens)
		return (1);
	i = 0;
	while (tokens[i])
	{
		cmd_node = ft_get_node(tokens, cmd_list, &i);
		if (!cmd_node)
		{
			ft_free_split((void **)tokens);
			ft_lstclean_cmd(cmd_list, ft_free_split);
			*cmd_list = NULL;
			return (0);
		}
	}
	return (1);
}
