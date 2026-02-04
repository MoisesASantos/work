/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:52:20 by mosantos          #+#    #+#             */
/*   Updated: 2026/01/28 19:15:14 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_read_command(t_shell *shell)
{
	if (!shell)
		return (0);
	if (shell->line)
		free(shell->line);
	shell->line = readline("minishell->mucuashell> ");
	if (shell->line == NULL)
	{
		printf("Exit\n");
		return (0);
	}
	if (shell->line[0] != '\0')
		add_history(shell->line);
	return (1);
}
