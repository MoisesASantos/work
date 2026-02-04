/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:26:05 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/17 18:55:29 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_cd(char **args, t_list *env)
{
	char	*oldpwd;
	char	*pwd;

	if (args[1] == NULL)
	{
		print_error_msg("cd", "expected argument to \"cd\"");
		return (1);
	}
	if (args[1] != NULL && args[2] != NULL)
	{
		print_error_msg(args[0], "too many arguments");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(args[1]) != 0)
	{
		print_perror_msg(args[0], args[1]);
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_set_env(&env, ft_strdup("OLDPWD"), oldpwd);
	ft_set_env(&env, ft_strdup("PWD"), pwd);
	return (0);
}
