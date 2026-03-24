/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:40:40 by mosantos          #+#    #+#             */
/*   Updated: 2025/10/08 11:58:33 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isvalid(char c, int base)
{
	static const char	lbase[] = "0123456789abcdef";
	static const char	ubase[] = "0123456789ABCDEF";
	int					i;

	i = 0;
	while (i < base)
	{
		if (c == lbase[i] || c == ubase[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_val(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static long	parse_result(const char *str, int sinal, int base, int *error)
{
	long	result;
	int		digit;

	result = 0;
	while (*str && ft_isvalid(*str, base))
	{
		digit = get_val(*str);
		if (digit < 0 || digit >= base)
			return (*error = 1, 0);
		if (sinal == 1 && result > (INT_MAX - digit) / base)
			return (*error = 1, 0);
		if (sinal == -1 && result > ((long)
				INT_MAX + 1 - digit) / base)
			return (*error = 1, 0);
		result = result * base + digit;
		str++;
	}
	if (*str && !ft_isvalid(*str, base))
		return (*error = 1, 0);
	return (result * sinal);
}

long	ft_atoll_base(const char *str, int base, int *error_flag)
{
	int	sinal;

	*error_flag = 0;
	sinal = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sinal = -1;
		str++;
	}
	if (!*str || !ft_isvalid(*str, base))
		return (*error_flag = 1, 0);
	if ((base == 16) && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	return (parse_result(str, sinal, base, error_flag));
}
