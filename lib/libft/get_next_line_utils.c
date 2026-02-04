/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:02:28 by mosantos          #+#    #+#             */
/*   Updated: 2025/08/13 13:20:56 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sttrchr_nl(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_sttrjoin(char *rest, const char *line)
{
	char	*joined;
	int		i;
	int		j;

	if (!rest)
		return (ft_strdup(line));
	joined = malloc(sizeof(char) * (ft_strlen(rest) + ft_strlen(line) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (rest[i])
	{
		joined[i] = rest[i];
		i++;
	}
	while (line[j])
	{
		joined[i] = line[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}
