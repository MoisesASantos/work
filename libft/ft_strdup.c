/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:44:06 by mcabeto           #+#    #+#             */
/*   Updated: 2026/01/07 12:39:07 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_s;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	new_s = (char *)malloc(len);
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s, len);
	return (new_s);
}
