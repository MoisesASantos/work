/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:59:56 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/25 17:29:45 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				i;

	if ((!dest || !src) && n > 0)
		return (NULL);
	i = 0;
	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
