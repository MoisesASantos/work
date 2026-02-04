/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:36:15 by mosantos          #+#    #+#             */
/*   Updated: 2025/07/04 06:46:23 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int	check_args(const char *str, va_list arg)
{
	if (str[1] == 'c')
		return (ft_puttchar_fd((char)va_arg(arg, int), 1));
	else if (str[1] == 's')
		return (ft_puttstr_fd(va_arg(arg, char *), 1));
	else if (str[1] == 'p')
		return (ft_handle_pointer(va_arg(arg, void *), 1));
	else if (str[1] == 'd' || str[1] == 'i')
		return (ft_puttnbr_fd(va_arg(arg, int), 1));
	else if (str[1] == 'u')
		return (ft_putnbr_unsigned_fd(va_arg(arg, unsigned int), 1));
	else if (str[1] == 'x')
		return (ft_putnbr_base_fd((unsigned long)va_arg(arg, unsigned int),
				"0123456789abcdef", 16, 1));
	else if (str[1] == 'X')
		return (ft_putnbr_base_fd((unsigned long)va_arg(arg, unsigned int),
				"0123456789ABCDEF", 16, 1));
	else if (str[1] == '%')
		return (ft_puttchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		count;

	if (!str)
		return (-1);
	va_start(arg, str);
	count = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1) && is_valid_specifier(*(str + 1)))
		{
			count += check_args(str, arg);
			str += 2;
		}
		else if (*str == '%' && ++str && *str)
			str++;
		else
		{
			write(1, str, 1);
			count++;
			str++;
		}
	}
	va_end(arg);
	return (count);
}
