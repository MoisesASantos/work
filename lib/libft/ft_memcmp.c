/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:39:12 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/25 23:26:24 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dest;
	const unsigned char	*src;
	size_t				i;

	if ((long)n < 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1 && n > 0)
		return (-1);
	if (!s2 && n > 0)
		return (1);
	dest = (const unsigned char *)s1;
	src = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (dest[i] != src[i])
			return ((int)dest[i] - (int)src[i]);
		i++;
	}
	return (0);
}
