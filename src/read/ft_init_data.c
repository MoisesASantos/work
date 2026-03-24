/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:33:13 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/20 19:31:49 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void    ft_init_mlx(t_mlx *mlx)
{
    t_img   *img;

    img = &mlx->img;
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
        exit(1);
    mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, screenWidth, screenHeight, "cub3D");
    mlx->img.img = mlx_new_image(mlx->mlx_ptr, screenWidth, screenHeight);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}