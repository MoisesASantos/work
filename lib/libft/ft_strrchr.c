/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:29:11 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/21 05:14:33 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_match;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	last_match = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last_match = ((char *)(s + i));
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (last_match);
}
