/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:26:00 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:34:47 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_env(t_list *env, char **args)
{
	t_env	*info;

	if (args[1])
	{
		print_error_msg(args[0], "no options env");
		return (1);
	}
	while (env)
	{
		info = (t_env *)env->content;
		if (info->key && info->value)
			printf("%s=%s\n", info->key, info->value);
		env = env->next;
	}
	return (0);
}
