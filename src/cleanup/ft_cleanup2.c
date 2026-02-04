/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:43:32 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:20:52 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_lstclean_redirect(t_redirect **redir)
{
	t_redirect	*aux;

	if (!redir)
		return ;
	while (*redir != NULL)
	{
		aux = *redir;
		*redir = (*redir)->next;
		free(aux->file_name);
		free(aux->limeter);
		if (aux->heredoc_fd != -1)
			close(aux->heredoc_fd);
		free(aux);
	}
	*redir = NULL;
}

void	ft_lstclean_cmd(t_cmd **lst, void (*del)(void**))
{
	t_cmd	*aux;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		aux = *lst;
		*lst = (*lst)->next;
		if (aux->argv)
			del((void **)aux->argv);
		ft_lstclean_redirect(&aux->redirects);
		free(aux);
	}
	*lst = NULL;
}

void	ft_free_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(content);
}

void	ft_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->line)
		free(shell->line);
	if (shell->cmd)
		ft_lstclean_cmd(&shell->cmd, ft_free_split);
	if (shell->env)
		ft_lstclear(&shell->env, ft_free_env);
	free(shell);
}
