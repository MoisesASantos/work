/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:35:16 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/18 17:05:59 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isvalid_number(char *str, int *status_code)
{
	int			i;
	int			sign;
	long long	result;
	int			has_digit;

	i = 0;
	result = 0;
	if (!str)
		return (1);
	sign = get_sign(str, &i);
	has_digit = parse_number(str, &i, sign, &result);
	if (!has_digit || str[i]
		|| is_overflow(sign, result))
		return (0);
	*status_code = (int)((sign * result) % 256);
	if (*status_code < 0)
		*status_code += 256;
	return (1);
}

int	execute_exit(t_data *data)

{
	int	status_code;
	int	ret;

	status_code = 0;
	ret = ft_isvalid_number(data->cmd.cmd_exec[1], &status_code);
	if(!ret)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		print_exit_error(data->cmd.cmd_exec[1], &status_code);
		exit(status_code);
	}
	if (data->cmd.cmd_exec[2])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(status_code);
}
