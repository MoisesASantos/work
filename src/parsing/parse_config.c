/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:46:30 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 19:46:23 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	parse_texture_directive(char **split, char **config_ptr, char *trimed)
{
	if (*config_ptr != NULL)
	{
		free(trimed);
		ft_free_split(split);
		exit_error("Duplicate declaration\n");
	}
	*config_ptr = get_texture_path(ft_strdup(split[1]));
}

static void	parse_split_config(char **split, t_data *data, char *trimed)
{
	if (ft_strcmp(split[0], "NO") == 0)
		parse_texture_directive(split, &data->config.no, trimed);
	else if (ft_strcmp(split[0], "SO") == 0)
		parse_texture_directive(split, &data->config.so, trimed);
	else if (ft_strcmp(split[0], "WE") == 0)
		parse_texture_directive(split, &data->config.we, trimed);
	else if (ft_strcmp(split[0], "EA") == 0)
		parse_texture_directive(split, &data->config.ea, trimed);
	else if (ft_strcmp(split[0], "F") == 0)
	{
		if(parse_floor_color(split, data))
			exit_error("Invalid floor color format\n");
	}
	else if (ft_strcmp(split[0], "C") == 0)
	{
		if(parse_ceiling_color(split, data))
			exit_error("Invalid ceiling color format\n");
	}
	else
	{
		free(trimed);
		ft_free_split(split);
		exit_error("Unknown configuration\n");
	}
}

void	parse_config_line(char *line, t_data *data)
{
	char	**split;
	char	*trimed;

	trimed = ft_strtrim(line, " \t\n");
	if (!trimed)
		exit_error("Memory allocation failed\n");
	split = ft_split(trimed, ' ');
	if (!split || !split[0] || !split[1])
	{
		free(trimed);
		ft_free_split(split);
		exit_error("Invalid config format\n");
	}
	parse_split_config(split, data, trimed);
	free(trimed);
	ft_free_split(split);
}

static char	*validate_texture_file(char *path)
{
	int	fd;
	int	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		exit(EXIT_FAILURE);
	}
	close(fd);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		ft_putstr_fd("Error: Texture must be .xpm: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		exit(EXIT_FAILURE);
	}
	return (path);
}

char	*get_texture_path(char *raw_path)
{
	char	*path;

	if (!raw_path)
		exit_error("Texture path is NULL\n");
	path = ft_strtrim(raw_path, " \t\n");
	if (!path)
		exit_error("Memory allocation failed\n");
	return (validate_texture_file(path));
}