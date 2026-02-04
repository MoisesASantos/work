/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:27:39 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/23 09:27:39 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*join_and_free(char *dest, char *src)
{
	char	*new_str;

	if (!dest)
		return (ft_strdup(src));
	if (!src)
		return (dest);
	new_str = ft_strjoin(dest, src);
	free(dest);
	return (new_str);
}

char	*append_char(char *str, char c)
{
	char	*new_str;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	if (!str)
		return (ft_strdup(tmp));
	new_str = ft_strjoin(str, tmp);
	free(str);
	return (new_str);
}

void	clean_empty_strs(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) == 0)
		{
			free(matrix[i]);
			j = i;
			while (matrix[j])
			{
				matrix[j] = matrix[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
}
