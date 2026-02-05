/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:11:41 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/21 12:59:13 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include <limits.h>

static int	ft_is_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = -1;
	if (str[++i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	result;
	long	prev;
	int		sign;
	int		i;

	if (!str)
		return (0);
	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + (str[i] - '0');
		if (result < 0 || (sign == 1 && result < prev) || \
(sign == -1 && result < 0 && prev >= 0))
			return (LONG_MIN);
		i++;
	}
	return (result * sign);
}

int	ft_exit(t_shell *shell, char **args)
{
	long	exit_code;

	if (ft_quant_matrix(args) > 2)
	{
		print_error_msg(args[0], "too many arguments");
		return (1);
	}
	else if (args[1] && !ft_is_number(args[1]))
	{
		print_error_msg(args[0], "numeric argument required");
		shell->is_run = 0;
		return (2);
	}
	shell->is_run = 0;
	printf("exit\n");
	if (!args[1])
		return (0);
	exit_code = ft_atol(args[1]);
	if (exit_code == LONG_MIN && \
ft_strncmp(args[1], "-9223372036854775808", 21) != 0)
	{
		print_error_msg(args[0], "numeric argument required");
		return (2);
	}
	return (exit_code & 0xFF);
}
