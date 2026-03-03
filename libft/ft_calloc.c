/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:16:51 by mcabeto           #+#    #+#             */
/*   Updated: 2025/07/01 12:30:27 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	size_full;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	size_full = nmemb * size;
	if (size_full / nmemb != size)
		return (NULL);
	ptr = malloc(size_full);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size_full);
	return (ptr);
}
