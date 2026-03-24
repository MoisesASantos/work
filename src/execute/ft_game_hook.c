/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:38:59 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/20 18:26:22 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_close_window(t_data *data)
{
    t_img   *img;

    img = &data->mlx.img;
	if (img->img)
		mlx_destroy_image(data->mlx.mlx_ptr, img->img);
	if (data->mlx.mlx_win)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	if (data->mlx.mlx_ptr)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
	exit(0);
    return (0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_close_window(data);
	return (0);
}