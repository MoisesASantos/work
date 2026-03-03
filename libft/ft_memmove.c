/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:19:57 by mcabeto           #+#    #+#             */
/*   Updated: 2025/07/04 12:00:55 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_memmove_first(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	ft_memmove_last(unsigned char *d, const unsigned char *s, size_t n)
{
	while (n > 0)
	{
		n--;
		d[n] = s[n];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d_ptr;
	const unsigned char	*s_ptr;

	if (n == 0)
		return (dest);
	if (!dest || !src)
		return (dest);
	d_ptr = (unsigned char *)dest;
	s_ptr = (const unsigned char *)src;
	if (d_ptr < s_ptr)
	{
		ft_memmove_first(d_ptr, s_ptr, n);
	}
	else
	{
		ft_memmove_last(d_ptr, s_ptr, n);
	}
	return (dest);
}
