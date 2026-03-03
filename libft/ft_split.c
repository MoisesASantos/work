/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:01:57 by mcabeto           #+#    #+#             */
/*   Updated: 2026/01/30 19:34:34 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	ft_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static void	ft_free_all(char **r, size_t i)
{
	while (i > 0)
	{
		i--;
		free(r[i]);
	}
	free(r);
}

static int	ft_fill_result(char **result, const char *s, char c)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			word_len = ft_word_len(s, c);
			result[i] = (char *) malloc(sizeof(char) * (word_len + 1));
			if (!result[i])
			{
				ft_free_all(result, i);
				return (0);
			}
			ft_strlcpy(result[i], s, word_len + 1);
			s += word_len;
			i++;
		}
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	result = (char **)malloc (sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	if (!ft_fill_result(result, s, c))
	{
		ft_free_all(result, num_words);
		return (NULL);
	}
	return (result);
}
