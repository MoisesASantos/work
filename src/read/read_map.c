/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:09:08 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 19:20:25 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	exit_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	open_map_file(char *file)
{
	int	fd;

	if (!file)
		exit_error("No file provide\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open file\n");
	return (fd);
}

void	process_config_line(char *line, t_data *data, int *in_map, 
						int line_num, int fd)
{
	if (is_config_line(line))
		parse_config_line(line, data);
	else if (is_map_valide(line))
	{
		*in_map = 1;
		data->map = add_line_to_map(data->map, line);
	}
	else
	{
		printf("Error (line %d): Invalid config line: '%s'\n", 
			line_num, line);
		close(fd);
		exit_error("Invalid configuration\n");
	}
}

void	process_map_line(char *line, t_data *data, int line_num, int fd)
{
	if (is_map_valide(line))
		data->map = add_line_to_map(data->map, line);
	else if (is_config_line(line))
	{
		printf("Error (line %d): Config found in map section: '%s'\n", 
			line_num, line);
		close(fd);
		exit_error("Configuration must come before map\n");
	}
	else
	{
		printf("Error (line %d): Invalid character in map: '%s'\n", 
			line_num, line);
		close(fd);
		exit_error("Invalid map line\n");
	}
}

void	calculate_map_width(t_data *data)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	data->map.map_width = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (data->map.map_data[i][j] != -2)
			j++;
		len = j;
		if (len > data->map.map_width)
			data->map.map_width = len;
		i++;
	}
}

int	read_map(char *file, t_data *data)
{
	int		fd;
	int		in_map;
	char	*line;
	int		line_num;

	fd = open_map_file(file);
	line_num = 0;
	in_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_num++;
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (!in_map)
			process_config_line(line, data, &in_map, line_num, fd);
		else
			process_map_line(line, data, line_num, fd);
		free(line);
	}
	close(fd);
	calculate_map_width(data);
	validate_complete_config(data);
	return (1);
}
