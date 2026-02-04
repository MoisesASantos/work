/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:48:02 by sgaspar           #+#    #+#             */
/*   Updated: 2026/02/02 16:54:08 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include "../include/structs.h"

void	ft_init_shell(char **envp, t_shell **shell)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->is_run = 1;
	(*shell)->exit_status = 0;
	load_env_2_shell(envp, *shell);
}
