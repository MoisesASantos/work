/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:46:59 by emjoao            #+#    #+#             */
/*   Updated: 2026/03/20 17:45:03 by emjoao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	exit_error_cleanup(t_data *data, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	if (data->config.no)
		free(data->config.no);
	if (data->config.so)
		free(data->config.so);
	if (data->config.we)
		free(data->config.we);
	if (data->config.ea)
		free(data->config.ea);
	if (data->map.map_data)
		free_map(data->map.map_data);
	exit(EXIT_FAILURE);
}

void	free_map(int **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}