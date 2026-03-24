/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:16:42 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 19:36:38 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int    parse_floor_color(char **split, t_data *data)
{
    char    **colors;
    int fleg_error;
    
    if (!split[1])
        exit_error("Floor color missing value\n");
    colors = ft_split(split[1], ',');
    if (!colors[0] || !colors[1] || !colors[2] || colors[3])
    {
        ft_free_split(colors);
        exit_error("Invalid floor color format (use: F r,g,b)\n");
    }
    data->config.floor.r = ft_atoll(ft_strtrim(colors[0], " \t\n"), &fleg_error);
    data->config.floor.g = ft_atoll(ft_strtrim(colors[1], " \t\n"), &fleg_error);
    data->config.floor.b = ft_atoll(ft_strtrim(colors[2], " \t\n"), &fleg_error);
    if (data->config.floor.r < 0 || data->config.floor.r > 255 ||
        data->config.floor.g < 0 || data->config.floor.g > 255 ||
        data->config.floor.b < 0 || data->config.floor.b > 255)
    {
        ft_free_split(colors);
        exit_error("RGB values must be between 0 and 255\n");
    }
    data->config.floor_set = 1;
    ft_free_split(colors);
    return (fleg_error);
}

int    parse_ceiling_color(char **split, t_data *data)
{
    char    **colors;
    int fleg_error;
    
    if (!split[1])
        exit_error("Ceiling color missing value\n");
    colors = ft_split(split[1], ',');
    if (!colors[0] || !colors[1] || !colors[2] || colors[3])
    {
        ft_free_split(colors);
        exit_error("Invalid ceiling color format (use: C r,g,b)\n");
    }
    data->config.ceiling.r = ft_atoll(ft_strtrim(colors[0], " \t\n"), &fleg_error);
    data->config.ceiling.g = ft_atoll(ft_strtrim(colors[1], " \t\n"), &fleg_error);
    data->config.ceiling.b = ft_atoll(ft_strtrim(colors[2], " \t\n"), &fleg_error);
    if (data->config.ceiling.r < 0 || data->config.ceiling.r > 255 ||
        data->config.ceiling.g < 0 || data->config.ceiling.g > 255 ||
        data->config.ceiling.b < 0 || data->config.ceiling.b > 255)
    {
        ft_free_split(colors);
        exit_error("RGB values must be between 0 and 255\n");
    }
    data->config.ceiling_set = 1;
    ft_free_split(colors);
    return (fleg_error);
}
