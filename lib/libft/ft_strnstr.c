/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:08:13 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/21 05:36:30 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	if (!big || !little)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	l_len = ft_strlen(little);
	if (len < l_len)
		return (NULL);
	while (*big != '\0' && len >= l_len)
	{
		i = 0;
		while (big[i] == little[i] && little[i] != '\0')
			i++;
		if (little[i] == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
