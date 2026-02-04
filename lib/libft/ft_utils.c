/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:36:51 by mosantos          #+#    #+#             */
/*   Updated: 2025/07/03 23:10:11 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puttchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_puttstr_fd(const char *str, int fd)
{
	int	count;

	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	count = 0;
	while (*str)
	{
		write(fd, str++, 1);
		count++;
	}
	return (count);
}

int	ft_putnbr_base_fd(unsigned long ptr, const char *base, int base_len, int fd)
{
	int	count;

	count = 0;
	if (!base || base_len <= 1)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	if (ptr == 0)
	{
		count += write(fd, &base[0], 1);
		return (count);
	}
	if (ptr >= (unsigned long)base_len)
		count += ft_putnbr_base_fd(ptr / base_len, base, base_len, fd);
	count += write(fd, &base[ptr % base_len], 1);
	return (count);
}

int	ft_puttnbr_fd(int n, int fd)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
	{
		count += write(fd, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	count += ft_putnbr_base_fd((unsigned int)n, "0123456789", 10, fd);
	return (count);
}

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	return (ft_putnbr_base_fd(n, "0123456789", 10, fd));
}
