/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 06:29:22 by mcabeto           #+#    #+#             */
/*   Updated: 2026/01/07 12:38:03 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_string_empty(void)
{
	char	*ptr_empty;

	ptr_empty = (char *)malloc(sizeof(char));
	if (!ptr_empty)
		return (NULL);
	ptr_empty[0] = '\0';
	return (ptr_empty);
}

static	size_t	ft_aux_len_substr(size_t len_s, unsigned int start, size_t len)
{
	if (len > (len_s - start))
		return (len_s - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	len_s;
	size_t	len_ptr;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		return (ft_string_empty());
	}
	len_ptr = ft_aux_len_substr(len_s, start, len);
	ptr = (char *)malloc(sizeof(char) * (len_ptr + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len_ptr)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
