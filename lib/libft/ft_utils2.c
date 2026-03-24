/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:58:58 by mosantos          #+#    #+#             */
/*   Updated: 2025/07/03 23:05:53 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handle_pointer(void *ptr, int fd)
{
	if (ptr == NULL)
		return (write(fd, "(nil)", 5));
	write(fd, "0x", 2);
	return (ft_putnbr_base_fd((unsigned long)ptr,
			"0123456789abcdef", 16, fd) + 2);
}

int	ft_quant_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (*p1 == *p2 && *p1 != '\0')
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
