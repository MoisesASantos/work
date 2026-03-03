/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabeto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:01 by mcabeto           #+#    #+#             */
/*   Updated: 2025/07/08 07:05:14 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_find_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_len_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_find_set(s1[i], set))
		i++;
	return (i);
}

static	size_t	ft_len_end(char const *s1, char const *set, size_t start)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	if (start == len)
		return (start);
	else
	{
		i = len - 1;
		while (i > start && ft_find_set(s1[i], set))
			i--;
		return (i + 1);
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = ft_len_start(s1, set);
	end = ft_len_end(s1, set, start);
	new_s = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new_s[i] = s1[start];
		i++;
		start++;
	}
	new_s[i] = '\0';
	return (new_s);
}
