/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:24:38 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/24 01:30:49 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iin_word(char const *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*malloc_word(char const *s, char c, int *index)
{
	char	*words;
	int		start;
	int		len;
	int		i;

	start = *index;
	i = 0;
	len = 0;
	while (s[start] && s[start] == c)
		start++;
	while (s[start + len] && s[start + len] != c)
		len++;
	words = malloc(sizeof(char) * (len + 1));
	if (!words)
		return (NULL);
	while (i < len)
	{
		words[i] = s[start + i];
		i++;
	}
	words[len] = '\0';
	*index = start + len;
	return (words);
}

static void	free_split(char **arr, int size)
{
	while (size > 0)
		free(arr[--size]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count_word;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	count_word = iin_word(s, c);
	result = malloc(sizeof(char *) * (count_word + 1));
	if (!result)
		return (NULL);
	while (j < count_word)
	{
		result[j] = malloc_word(s, c, &i);
		if (!result[j])
		{
			free_split(result, j);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}
