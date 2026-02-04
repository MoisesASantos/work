/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:45:40 by mosantos          #+#    #+#             */
/*   Updated: 2025/06/17 15:24:44 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n != 0 && ++len)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = get_num_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		res[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
