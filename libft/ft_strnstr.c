/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:10:14 by mcabeto           #+#    #+#             */
/*   Updated: 2025/06/23 13:48:37 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	if (!little)
		return (NULL);
	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	if (!big)
		return (NULL);
	i = 0;
	while (i < len && (len - i) >= len_little)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(&big[i], little, len_little) == 0)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
