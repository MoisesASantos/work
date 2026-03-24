/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:06:10 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 19:07:19 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_cab_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	set_player_direction(t_data *data, int direction)
{
	if (direction == MAP_NORTH)
	{
		data->player.dirX = 0;
		data->player.dirY = -1;
		data->game.planeX = 0.66;
		data->game.planeY = 0;
	}
	else if (direction == MAP_SOUTH)
	{
		data->player.dirX = 0;
		data->player.dirY = 1;
		data->game.planeX = -0.66;
		data->game.planeY = 0;
	}
	else if (direction == MAP_EAST)
	{
		data->player.dirX = 1;
		data->player.dirY = 0;
		data->game.planeX = 0;
		data->game.planeY = 0.66;
	}
	else if (direction == MAP_WEST)
	{
		data->player.dirX = -1;
		data->player.dirY = 0;
		data->game.planeX = 0;
		data->game.planeY = -0.66;
	}
}

static int	find_and_init_player(t_data *data)
{
	int	i;
	int	j;
	int	cell;

	i = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (j < data->map.map_width)
		{
			cell = data->map.map_data[i][j];
			if (cell == MAP_NORTH || cell == MAP_SOUTH
				|| cell == MAP_EAST || cell == MAP_WEST)
			{
				data->player.posX = j + 0.5;
				data->player.posY = i + 0.5;
				set_player_direction(data, cell);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	init_player(t_data *data)
{
	return (find_and_init_player(data));
}