/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:27:43 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/19 15:27:45 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

int get_texture_pixel(t_texture *texture, int x, int y)
{
    char *dst;

    dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
    return (*(unsigned int *)dst);
}

static void    ft_draw_pixels(t_data *data, t_texture *texture, int x)
{
    int y;
    int z;

    y = data->dda.drawStart;
    z = 0;
    while (++z < data->dda.drawStart)
        my_put_pixel_to_image(&data->mlx.img, x, z, ft_rgb(data->config.ceiling));
    while (y <= data->dda.drawEnd)
    {
        texture->texY = (int)texture->texPos & (texture->height - 1);
        texture->texPos += texture->stepText;
        texture->color = get_texture_pixel(texture, texture->texX, texture->texY);
        if (data->dda.side == 1)
            texture->color = (texture->color >> 1) & 8355711;
        my_put_pixel_to_image(&data->mlx.img, x, y, texture->color);
        y++;
    }
    y = data->dda.drawEnd + 1;
    while (y < screenHeight)
    {
        my_put_pixel_to_image(&data->mlx.img, x, y, ft_rgb(data->config.floor));
        y++;
    }
}

void    ft_texture(t_data *data, double perWallDist, int x)
{
    t_texture   *texture;

    if (data->dda.side == 0 && data->game.rayDirX > 0)
        texture = &data->texture[TEX_WEST];
    if (data->dda.side == 0 && data->game.rayDirX < 0)
        texture = &data->texture[TEX_EAST];
    if (data->dda.side == 1 && data->game.rayDirY > 0)
        texture = &data->texture[TEX_NORTH];
    if (data->dda.side == 1 && data->game.rayDirY < 0)
        texture = &data->texture[TEX_SOUTH];
    if (data->dda.side == 0)
        texture->wallX = data->player.posY + perWallDist * data->game.rayDirY;
    else
        texture->wallX = data->player.posX + perWallDist * data->game.rayDirX;
    texture->wallX -= floor((texture->wallX));
    texture->texX = (int)(texture->wallX * texture->width);
    if (data->dda.side == 0 && data->game.rayDirX > 0)
        texture->texX = texture->width - texture->texX - 1;
    else if (data->dda.side == 1 && data->game.rayDirY < 0)
        texture->texX = texture->width - texture->texX - 1;
    texture->stepText = 1.0 * texture->height / data->dda.lineHeight;
    texture->texPos = (data->dda.drawStart - screenHeight / 2 + data->dda.lineHeight / 2) * texture->stepText;
    ft_draw_pixels(data, texture, x);
}