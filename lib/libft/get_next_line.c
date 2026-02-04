/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:02:14 by mosantos          #+#    #+#             */
/*   Updated: 2025/08/13 13:21:21 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *rest)
{
	int	i;

	if (!rest || rest[0] == '\0')
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	return (ft_substr(rest, 0, i));
}

char	*get_update(char *rest)
{
	char	*line;
	int		i;

	if (!rest || rest[0] == '\0')
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	if (rest[i] == '\0')
	{
		free(rest);
		return (NULL);
	}
	line = ft_substr(rest, i, (ft_strlen(rest) - i));
	free(rest);
	return (line);
}

char	*ft_read_buffer(char **rest, int fd)
{
	char	*line;
	char	*temp;
	int		bytes;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	bytes = 1;
	while (!ft_sttrchr_nl(*rest) && bytes > 0)
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		line[bytes] = '\0';
		temp = ft_sttrjoin(*rest, line);
		if (!temp)
			return (free(line), free(*rest), *rest = NULL, NULL);
		free(*rest);
		*rest = temp;
	}
	free(line);
	return (*rest);
}

char	*ft_engine(char **rest, int fd)
{
	char	*result;

	if (!ft_read_buffer(rest, fd))
		return (NULL);
	if (!*rest || (*rest)[0] == '\0')
		return (NULL);
	result = get_line(*rest);
	*rest = get_update(*rest);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*rest_word;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (ft_engine(&rest_word, fd));
}
