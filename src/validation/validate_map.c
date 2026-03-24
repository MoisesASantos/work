/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:06:46 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 18:34:13 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	validate_map_spawn(t_data *data)
{
	int	x;
	int	y;
	int	spawn_count;
	int	len;
	int	cell;

	y = 0;
	spawn_count = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		len = data->map.map_width;
		while (x < len && data->map.map_data[y][x] != -2)
		{
			cell = data->map.map_data[y][x];
			if (cell == MAP_NORTH || cell == MAP_SOUTH
				|| cell == MAP_EAST || cell == MAP_WEST)
				spawn_count++;
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
		exit_error("No spawn point found in map\n");
	else if (spawn_count > 1)
		exit_error("Multiple spawn points found in map\n");
}

void	validate_complete_config(t_data *data)
{
	if (!data->config.no)
		exit_error("Missing NO (north texture) configuration\n");
	if (!data->config.so)
		exit_error("Missing SO (south texture) configuration\n");
	if (!data->config.we)
		exit_error("Missing WE (west texture) configuration\n");
	if (!data->config.ea)
		exit_error("Missing EA (east texture) configuration\n");
	if (!data->config.floor_set)
		exit_error("Missing F (floor color) configuration\n");
	if (!data->config.ceiling_set)
		exit_error("Missing C (ceiling color) configuration\n");
	if (data->map.map_height == 0)
		exit_error("No map found\n");
	validate_map_spawn(data);
	validate_map_cells(data);
}
