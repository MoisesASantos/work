/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:46:45 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/24 11:08:00 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_map_valide(char *line)
{
	if (!line || !line[0])
		return (0);
	while (*line && *line != '\n')
	{
		if (*line != '1' && *line != '0' &&
			 *line != 'N' && *line != ' ' &&
			 *line != 'E' && *line != 'W' &&
			  *line != 'S')
			return (0);
		line++;
	}
	return (1);
}

static int	char_to_map_int(char c)
{
	if (c == '0')
		return (MAP_FLOOR);
	if (c == '1')
		return (MAP_WALL);
	if (c == 'N')
		return (MAP_NORTH);
	if (c == 'S')
		return (MAP_SOUTH);
	if (c == 'E')
		return (MAP_EAST);
	if (c == 'W')
		return (MAP_WEST);
	return (MAP_EMPTY);
}

static int	*line_to_int_row(char *line)
{
	int	len;
	int	i;
	int	*row;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	row = (int *)malloc(sizeof(int) * (len + 1));
	if (!row)
		exit_error("Memory allocation failed\n");
	i = 0;
	while (i < len)
	{
		row[i] = char_to_map_int(line[i]);
		i++;
	}
	row[len] = -2;
	return (row);
}

t_map	add_line_to_map(t_map map, char *line)
{
	int	**new_map;
	int	i;

	new_map = (int **)malloc(sizeof(int *) * (map.map_height + 2));
	if (!new_map)
		exit_error("Memory allocation failed\n");
	i = 0;
	while (i < map.map_height)
	{
		new_map[i] = map.map_data[i];
		i++;
	}
	new_map[i] = line_to_int_row(line);
	new_map[i + 1] = NULL;
	free(map.map_data);
	return ((t_map){.map_data = new_map, .map_width = map.map_width,
		.map_height = map.map_height + 1});
}

int	is_config_line(char *line)
{
	char	*trimmed;
	int		result;

	if (!line || line[0] == '\0')
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	result = (
		ft_strncmp(trimmed, "NO", 2) == 0 ||
		ft_strncmp(trimmed, "SO", 2) == 0 ||
		ft_strncmp(trimmed, "WE", 2) == 0 ||
		ft_strncmp(trimmed, "EA", 2) == 0 ||
		ft_strncmp(trimmed, "F", 1) == 0 ||
		ft_strncmp(trimmed, "C", 1) == 0
	);
	free(trimmed);
	return (result);
}