/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:58:21 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/24 08:54:02 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void    ft_check_side(t_data *data)
{
    if (data->game.rayDirX < 0)
    {
        data->player.stepX = -1;
        data->dda.sideDistX = (data->player.posX - data->game.mapX) * data->dda.deltaDistX;
    }
    else
    {
        data->player.stepX = 1;
        data->dda.sideDistX = (data->player.posX + 1.0 - data->game.mapX) * data->dda.deltaDistX;
    }
    if (data->game.rayDirY < 0)
    {
        data->player.stepY = -1;
        data->dda.sideDistY = (data->player.posY - data->game.mapY) * data->dda.deltaDistY;
    }
    else
    {
        data->player.stepY = 1;
        data->dda.sideDistY = (data->player.posY + 1.0 - data->game.mapY) * data->dda.deltaDistY;
    }
}

static void    ft_init_params(t_data *data, int x)
{
    data->game.cameraX = 2 * x / (double)screenWidth - 1;
    data->game.rayDirX = data->player.dirX + data->game.planeX * data->game.cameraX;
    data->game.rayDirY = data->player.dirY + data->game.planeY * data->game.cameraX;
    data->game.mapX = (int)data->player.posX;
    data->game.mapY = (int)data->player.posY;
    if (data->game.rayDirX == 0)
        data->dda.deltaDistX = 1e30;
    else
        data->dda.deltaDistX = fabs(1 / data->game.rayDirX);
    if (data->game.rayDirY == 0)
        data->dda.deltaDistY = 1e30;
    else
        data->dda.deltaDistY = fabs(1 / data->game.rayDirY);
    ft_check_side(data);
}

static void    ft_dda(t_data *data)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (data->dda.sideDistX < data->dda.sideDistY)
        {
            data->game.mapX += data->player.stepX;
            data->dda.sideDistX += data->dda.deltaDistX;
            data->dda.side = 0;
        }
        else
        {
            data->game.mapY += data->player.stepY;
            data->dda.sideDistY += data->dda.deltaDistY;
            data->dda.side = 1;
        }
        if (data->map.map_data[data->game.mapX][data->game.mapY] == 1)
            hit = 1;
    } 
}

static void    ft_check_height(t_data *data, double *perWallDist)
{
    if (data->dda.side == 0)
        *perWallDist = (data->dda.sideDistX - data->dda.deltaDistX);
    else
        *perWallDist = (data->dda.sideDistY - data->dda.deltaDistY); 
    data->dda.lineHeight = (int)(screenHeight / *perWallDist);
    data->dda.drawStart = -data->dda.lineHeight / 2 + screenHeight / 2;
    data->dda.drawEnd = data->dda.lineHeight / 2 + screenHeight / 2;
    if (data->dda.drawStart < 0)
        data->dda.drawStart = 0;
    if (data->dda.drawEnd <= 0)
        data->dda.drawEnd = screenHeight - 1;
}

void ft_render(t_data *data)
{
    int x;
    double  perWallDist;

    x = 0;
    perWallDist = 0.0;
    while (x < screenWidth)
    {
        ft_init_params(data, x);
        ft_dda(data);
        ft_check_height(data, &perWallDist);
        ft_texture(data, perWallDist, x);
        x++;
    }
}