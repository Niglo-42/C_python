/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:36:05 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 11:37:11 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "list/list.h"
#include "tuple/tuple.h"
#include "dict/dict.h"

char	*ft_itoa(char *buf, long n, size_t base)
{
	long	nb;
	int		i;
	int		sign;

	i = (n == 0);
	sign = (n < 0);
	nb = n * (n >= 0) + (-n * (n < 0));
	n = nb;
	while (n > 0 && ++i)
		n = n / base;
	buf[i + sign] = 0;
	buf[0] = 0;
	while (i-- > 0)
	{
		buf[i + sign] = "0123456789abcdef"[nb % base];
		nb = nb / base;
	}
	return (buf[0] += '-' * sign, buf);
}

void	display_error(char *s, int *value, size_t base)
{
	char	nb[13];
	t_error	error;

	memcpy(error.e, s, strlen(s) + 1);
	if (value)
	{
		strcat(error.e, ft_itoa(nb, *(long *)value, base));
		strcat(error.e, "\n");
	}
	write(1, error.e, strlen(error.e));
}

int	minmax(int a, int b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}
