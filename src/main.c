/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:54:57 by mosantos          #+#    #+#             */
/*   Updated: 2026/01/27 19:48:17 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./include/shell.h"
#include "include/ft_handle_input.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**lexer_cmd;
	int		exit_status;

	(void)argc;
	(void)argv;
	lexer_cmd = NULL;
	ft_main_signals();
	ft_init_shell(envp, &shell);
	if (!shell)
		return (EXIT_FAILURE);
	while (shell->is_run)
	{
		minishell(shell, lexer_cmd);
		if (!shell->line && !shell->is_run)
			break ;
	}
	exit_status = shell->exit_status;
	ft_cleanup_shell(shell);
	rl_clear_history();
	return (exit_status);
}
