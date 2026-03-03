/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:07:53 by cjeronim          #+#    #+#             */
/*   Updated: 2026/02/18 17:46:12 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_count_list(t_env *data)

{
	int		i;
	t_env	*aux;

	i = 0;
	aux = data;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

static void	ft_bubble_sort(t_env **array, int size_list)

{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < (size_list - 1))
	{
		j = i + 1;
		while (j < size_list)
		{
			if (ft_strcmp(array[i]->name, array[j]->name) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_env	**order_export(t_env *data)

{
	int		i;
	int		size_list;
	t_env	**array;
	t_env	*aux;

	size_list = ft_count_list(data);
	array = malloc((size_list + 1) * sizeof(t_env *));
	aux = data;
	i = 0;
	while (i < size_list)
	{
		array[i] = aux;
		i++;
		aux = aux->next;
	}
	array[i] = NULL;
	ft_bubble_sort(array, size_list);
	return (array);
}
