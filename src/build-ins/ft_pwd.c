/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:25 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 12:36:05 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		print_error_msg("pwd", "something gone wrong");
		return (1);
	}
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
