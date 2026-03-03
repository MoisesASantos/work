/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_syntax_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:51:22 by cjeronim          #+#    #+#             */
/*   Updated: 2026/03/03 09:45:30 by mcabeto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_redirect_output(t_data *data, int i)

{
	if (ft_strlen(data->token[i]) > 3)
	{
		print_error(data,
			"Error: syntax error near unexpected token \'>>\'", 2);
		return (1);
	}
	else if (ft_strlen(data->token[i]) > 2)
	{
		print_error(data,
			"Error: syntax error near unexpected token \'>\'", 2);
		return (1);
	}
	else if (ft_strchr(data->token[i + 1], '<'))
	{
		if (ft_strlen(data->token[i + 1]) > 1)
			return (print_error(data,
					"Error: syntax error near unexpected token \'<<\'", 2), 1);
		else
			return (print_error(data,
					"Error: syntax error near unexpected token \'<\'", 2), 1);
	}
	return (0);
}

int	found_redirect_input(t_data *data, int i)

{
	if (ft_strlen(data->token[i]) > 3)
	{
		print_error(data,
			"Error: syntax error near unexpected token \'<<\'", 2);
		return (1);
	}
	else if (ft_strlen(data->token[i]) > 2)
	{
		print_error(data,
			"Error: syntax error near unexpected token \'<\'", 2);
		return (1);
	}
	else if (ft_strchr(data->token[i + 1], '>'))
	{
		if (ft_strlen(data->token[i + 1]) > 1)
			return (print_error(data,
					"Error: syntax error near unexpected token \'>>\'", 2), 1);
		else
			return (print_error(data,
					"Error: syntax error near unexpected token \'>\'", 2), 1);
	}
	return (0);
}
