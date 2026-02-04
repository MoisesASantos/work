/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:04:44 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/01 11:20:05 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_free_split(void **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_error_msg(char *str, char *src)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(src, 2);
	ft_putstr_fd("'\n", 2);
}

void	print_perror_msg(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	print_error_msg(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
