/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:51:14 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/20 19:30:03 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3D.h"



int main(int argc, char **argv)
{
    t_data  data;
    if (argc != 2)
		    exit_error("Uso: ./cub3D <map.cub>");
	  if(!is_cab_file(argv[1]))
		    exit_error("The file must have a .cub extension\n");
    ft_memset(&data, 0, sizeof(t_data));
    read_map(argv[1], &data);
    for (int y = 0; y < data.map.map_height; y++)
    {
        for (int x = 0; x < data.map.map_width; x++)
        {
            printf("%d ", data.map.map_data[y][x]);
        }
        printf("\n");
    }
    init_player(&data);
    ft_init_mlx(&data.mlx);
    load_textures(&data, data.texture);
    ft_render(&data);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.mlx_win, data.mlx.img.img, 0, 0);
    mlx_hook(data.mlx.mlx_win, KeyPress, KeyPressMask, ft_key_hook, &data);
    mlx_hook(data.mlx.mlx_win, 17, 0, ft_close_window, &data);
	  mlx_loop(data.mlx.mlx_ptr);
    return (0);
}