/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:39:01 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:29:50 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	ft_heredoc_treatment(t_shell *shell)
{
	t_cmd		*aux;
	t_redirect	*redir;
	int			status;

	if (!shell->cmd)
		return (0);
	aux = shell->cmd;
	status = 0;
	while (aux)
	{
		redir = aux->redirects;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				status = ft_handle_heredoc(shell, redir);
				if (status != 0)
					return (status);
			}
			redir = redir->next;
		}
		aux = aux->next;
	}
	return (status);
}

static void	execute_commands(t_shell *shell)
{
	if (!shell || !shell->cmd)
		return ;
	if (shell->cmd->next != NULL)
		shell->exit_status = ft_execute_multiple_cmd(shell);
	else
		shell->exit_status = execute_one_command(shell);
}

static int	ft_process_input(t_shell *shell)
{
	int	syntax_err;

	if (!ft_read_command(shell))
	{
		shell->is_run = 0;
		return (0);
	}
	if (!shell->line || shell->line[0] == '\0')
		return (0);
	syntax_err = ft_syntax_error(shell->line);
	if (syntax_err)
	{
		shell->exit_status = syntax_err;
		free(shell->line);
		shell->line = NULL;
		return (0);
	}
	return (1);
}

static int	ft_process_commands(t_shell *shell, char **lexer_cmd)
{
	int	status;

	if (ft_parse(lexer_cmd, &shell->cmd) == 0)
	{
		shell->exit_status = 2;
		return (0);
	}
	status = ft_heredoc_treatment(shell);
	if (status != 0)
	{
		shell->exit_status = status;
		ft_lstclean_cmd(&shell->cmd, ft_free_split);
		return (0);
	}
	return (1);
}

void	minishell(t_shell *shell, char **lexer_cmd)
{
	char	*line;

	if (!shell)
		return ;
	if (shell->cmd)
		ft_lstclean_cmd(&shell->cmd, ft_free_split);
	if (!ft_process_input(shell))
		return ;
	line = ft_strtrim(shell->line, " ");
	free(shell->line);
	shell->line = NULL;
	if (!line)
		line = ft_strdup("");
	lexer_cmd = lexer(shell, line);
	if (!lexer_cmd)
		return ;
	if (!ft_process_commands(shell, lexer_cmd))
	{
		ft_free_split((void **)lexer_cmd);
		return ;
	}
	ft_set_env(&shell->env, ft_strdup("_"), ft_strdup(lexer_cmd[0]));
	execute_commands(shell);
	ft_free_split((void **)lexer_cmd);
}
