/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:10:21 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/25 17:31:01 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				i;

	if ((!dest || !src) && n > 0)
		return (NULL);
	i = 0;
	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	if (s1 < s2)
	{
		while (i < n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			s1[i] = s2[i];
	}
	return (dest);
}
