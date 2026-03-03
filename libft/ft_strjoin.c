/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:25:10 by mcabeto           #+#    #+#             */
/*   Updated: 2026/01/21 19:03:12 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_s = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, (len_s1 + len_s2 + 1));
	ft_strlcat(new_s, s2, (len_s1 + len_s2 + 1));
	new_s[len_s1 + len_s2] = '\0';
	return (new_s);
}
