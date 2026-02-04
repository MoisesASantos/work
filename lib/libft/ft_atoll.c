/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:26:18 by mosantos          #+#    #+#             */
/*   Updated: 2025/09/17 13:28:41 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	parse_digits(const char *nptr, int sign, int *error_flag)
{
	long	result;
	int		digit;

	result = 0;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if (sign == 1 && result > (INT_MAX - digit) / 10)
			return (*error_flag = 1, 0);
		if (sign == -1 && result > ((long)
				INT_MAX + 1 - digit) / 10)
			return (*error_flag = 1, 0);
		result = result * 10 + digit;
		nptr++;
	}
	return (result * sign);
}

long	ft_atoll(const char *nptr, int *error_flag)
{
	int	sign;

	sign = 1;
	if (!nptr)
	{
		ft_putendl_fd("Error", 2);
		exit(1);
	}
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (!ft_isdigit(*nptr))
		return (*error_flag = 1, 0);
	return (parse_digits(nptr, sign, error_flag));
}
