/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:36 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:33:23 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	check_invalid_flag(char *str)
{
	int	j;
	int	flag_off;

	j = 2;
	flag_off = 0;
	while (str[j])
	{
		if (str[j] != 'n' && str[j] != '\0')
		{
			flag_off = 1;
			break ;
		}
		j++;
	}
	return (flag_off);
}

int	ft_echo(char **args)
{
	int	flag_in;
	int	i;

	if (!args)
		return (1);
	flag_in = 0;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		if (check_invalid_flag(args[i]))
			break ;
		flag_in = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag_in == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
