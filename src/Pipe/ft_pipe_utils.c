/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:33:03 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/17 18:47:37 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_save_original_fd(int original_fd[2])
{
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
}

void	ft_restore_fd(int original_fd[2])
{
	if (original_fd[0] != STDIN_FILENO)
		dup2(original_fd[0], STDIN_FILENO);
	if (original_fd[1] != STDOUT_FILENO)
		dup2(original_fd[1], STDOUT_FILENO);
}
