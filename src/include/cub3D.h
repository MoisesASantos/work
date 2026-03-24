/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:30:41 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/24 11:08:24 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "structs.h"
#include "../../lib/libft/libft.h"

//read functions
int     read_map(char *file, t_data *data);
void    ft_init_mlx(t_mlx *mlx);
//render functions
void    ft_render(t_data *data);
void	my_put_pixel_to_image(t_img *img, int x, int y, int color);
//parsing functions
void    parse_config_line(char *line, t_data *data);
int     parse_floor_color(char **split, t_data *data);
int     parse_ceiling_color(char **split, t_data *data);
char    *get_texture_path(char *path);
//validation functions
void    validate_map_spawn(t_data *data);
void    validate_map_cells(t_data *data);
void    validate_complete_config(t_data *data);
void    validate_flood_fill(t_data *data);
t_map	add_line_to_map(t_map map, char *line);
int		is_empty_line(char *line);
int		is_cab_file(char *filename);
int		is_map_valide(char *line);
int		is_config_line(char *line);
int		init_player(t_data *data);
//utils functions
void    ft_free_split(char **split);
void    exit_error(char *msg);
void    exit_error_cleanup(t_data *data, char *msg);
void    free_map(int **map);
void        load_textures(t_data *data, t_texture *img_textures);
t_texture   *get_wall_texture(t_data *data);

//hook functions
int ft_close_window(t_data *data);
int	ft_key_hook(int keycode, t_data *data);
//texture functions
void    ft_texture(t_data *data, double perWallDist, int x);

#endif
