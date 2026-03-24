/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:48:12 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/24 13:14:00 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	load_texture(t_data *data, t_texture *tex, char *path)
{
	tex->img_texture = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img_texture)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img_texture, &tex->bpp,
			&tex->line_length, &tex->endian);
	return (1);
}

t_texture	*get_wall_texture(t_data *data)
{
	if (data->dda.side == 1)
	{
		if (data->game.rayDirY > 0)
			return (&data->texture[TEX_SOUTH]);
		return (&data->texture[TEX_NORTH]);
	}
	if (data->game.rayDirX > 0)
		return (&data->texture[TEX_EAST]);
	return (&data->texture[TEX_WEST]);
}

void	load_textures(t_data *data, t_texture *img_textures)
{
	int	i;

	if (!load_texture(data, &img_textures[TEX_NORTH], data->config.no)
		|| !load_texture(data, &img_textures[TEX_SOUTH], data->config.so)
		|| !load_texture(data, &img_textures[TEX_WEST], data->config.we)
		|| !load_texture(data, &img_textures[TEX_EAST], data->config.ea))
	{
		i = 0;
		while (i < 4)
		{
			if (img_textures[i].img_texture)
				mlx_destroy_image(data->mlx.mlx_ptr, img_textures[i].img_texture);
			i++;
		}
		exit_error("Failed to load all textures\n");
	}
}
