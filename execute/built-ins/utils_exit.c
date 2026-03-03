/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:45:27 by cjeronim          #+#    #+#             */
/*   Updated: 2026/01/28 19:53:07 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	is_overflow(int sign, long long result)
{
	if ((sign == 1 && result > LLONG_MAX)
		|| (sign == -1 && (-result < LLONG_MIN)))
		return (1);
	return (0);
}

int	print_exit_error(char *str, int *status_code)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	*status_code = 2;
	return (0);
}

int	parse_number(char *str, int *i, int sign, long long *res)

{
	int	has_digit;

	has_digit = 0;
	while (ft_isdigit(str[*i]))
	{
		has_digit = 1;
		*res = *res * 10 + (str[*i] - '0');
		if (is_overflow(sign, *res))
			return (has_digit);
		(*i)++;
	}
	return (has_digit);
}
