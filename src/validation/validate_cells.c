/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cells.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:45:37 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/24 11:08:13 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	row_len(int *row)
{
	int	len;

	len = 0;
	if (!row)
		return (0);
	while (row[len] != -2)
		len++;
	return (len);
}

int	is_valid_neighbor(int **map, int x, int y, int max_y)
{
	if (y < 0 || y >= max_y)
		return (0);
	if (x < 0)
		return (0);
	if (x >= row_len(map[y]))
		return (0);
	if (map[y][x] == MAP_EMPTY)
		return (0);
	return (1);
}

int	validate_cell(int **map, int x, int y, int max_y)
{
	int	cell;

	cell = map[y][x];
	if (cell == MAP_WALL || cell == MAP_EMPTY || cell == -2)
		return (1);
	if (cell == MAP_FLOOR || cell == MAP_NORTH || cell == MAP_SOUTH
		|| cell == MAP_EAST || cell == MAP_WEST)
	{
		if (!is_valid_neighbor(map, x - 1, y, max_y))
			return (0);
		if (!is_valid_neighbor(map, x + 1, y, max_y))
			return (0);
		if (!is_valid_neighbor(map, x, y - 1, max_y))
			return (0);
		if (!is_valid_neighbor(map, x, y + 1, max_y))
			return (0);
		return (1);
	}
	return (0);
}

void	validate_map_cells(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		while (x < row_len(data->map.map_data[y]))
		{
			if (!validate_cell(data->map.map_data, x, y, data->map.map_height))
			{
				printf("Error: Invalid cell at (%d, %d)\n", x, y);
				exit_error("Map is not properly enclosed by walls\n");
			}
			x++;
		}
		y++;
	}
}