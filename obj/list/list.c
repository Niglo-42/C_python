/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:43:13 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 10:51:52 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "../tuple/tuple.h"
#include "../dict/dict.h"

t_list	*list_new(size_t n, t_arena *arena, va_list data)
{
	size_t	i;
	t_list	*self;

	i = -1;
	self = (t_list *)get_memory(
			sizeof(t_list) + ((n + 1) * 2) * sizeof(t_obj *), arena);
	if (!self)
		return (NULL);
	self->cap = (n + 1) * 2;
	self->size = n;
	self->base.refcnt = 0;
	self->base.type = V_LIST;
	while (++i < n)
		self->members[i] = va_arg(data, t_obj *);
	return (self);
}

t_list	*lst(t_arena *arena, int n, ...)
{
	va_list	lst;

	va_start(lst, n);
	return (list_new(n, arena, lst));
}

void	print_list(t_list *self)
{
	size_t	i;

	i = 0;
	write(1, "[", 1);
	while (i < self->size)
	{
		print_obj(self->members[i++]);
		write(1, ", ", 2 * (self->size > i));
	}
	write(1, "]\n", 2);
}

int	handle_error(t_list *self, int start, int end)
{
	if (start < 0 || start >= (int)self->size)
	{
		return (display_error(
				"OutOfRangeError, given start index: ", &start, 10), 1);
	}
	if (end < -1 || end > (int)self->size)
		return (display_error(
				"OutOfRangeError, given end index: ", &end, 10), 1);
	return (0);
}
