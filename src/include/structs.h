/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:10:55 by mosantos          #+#    #+#             */
/*   Updated: 2026/03/24 11:08:19 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../../lib/libft/libft.h"
#include "../../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <math.h>
#include <sys/time.h>
#define screenWidth 1920
#define screenHeight 1080

#define MAP_EMPTY  -1
#define MAP_FLOOR   0
#define MAP_WALL    1
#define MAP_NORTH   2
#define MAP_SOUTH   3
#define MAP_EAST    4
#define MAP_WEST    5

typedef struct s_img
{
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_texture
{
    void    *img_texture;
    char    *addr;
    double  wallX;
    double  stepText;
    double  texPos;
    int     texX;
    int     texY;
    int     width;
    int     height;
    int     bpp;
    int     color;
    int     line_length;
    int     endian;
} t_texture;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *mlx_win;
    t_img   img;
}   t_mlx;

typedef struct s_player
{
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    int     stepX;
    int     stepY;
}   t_player;

typedef struct s_game
{
    double  rayDirX;
    double  rayDirY;
    double  planeX;
    double  planeY;
    double  cameraX;
    double  time;
    double  oldTime;
    double  frameTime;
    double  move_speed;
    double  rot_speed;
    int     mapX;
    int     mapY;
}   t_game;

typedef struct s_dda
{
    double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;
    int     side;
    int     lineHeight;
    int     drawEnd;
    int     drawStart;
}   t_dda;

typedef struct s_config
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    t_color floor;
    t_color ceiling;
    int floor_set;
    int ceiling_set;
}   t_config;

typedef struct s_map
{
    int **map_data;
    int map_width;
    int map_height;
}   t_map;

typedef struct  s_data
{
    t_mlx       mlx;
    t_game      game;
    t_map       map;
    t_player    player;
    t_texture   texture[4];
    t_config    config;
    t_dda       dda;
}   t_data;

typedef enum e_texture_id
{
    TEX_NORTH,
    TEX_SOUTH,
    TEX_WEST,
    TEX_EAST
}   t_texture_id;

#endif
