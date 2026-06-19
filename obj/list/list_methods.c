/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:47:05 by tbelard           #+#    #+#             */
/*   Updated: 2026/06/19 11:56:10 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "../tuple/tuple.h"
#include "../dict/dict.h"

static int	apply_step(int *start, int step)
{
	*start += step;
	return (*start - step);
}

static t_list	*realloc_list(t_list *old, t_arena *arena)
{
	size_t	new_cap;
	t_list	*new;
	size_t	i;

	new_cap = old->cap * 2;
	new = (t_list *)get_memory(
			sizeof(t_list) + new_cap * sizeof(t_obj *), arena);
	new->base = old->base;
	new->size = old->size;
	new->cap = new_cap;
	i = 0;
	while (i < old->size)
	{
		new->members[i] = old->members[i];
		i++;
	}
	return (new);
}

t_list	*slice(t_list *self, int *range, t_arena *arena)
{
	t_list	*list;
	int		upper;
	int		start;
	int		end;
	int		step;

	start = range[0];
	end = range[1];
	step = range[2];
	upper = self->size -1;
	if (start < 0)
		start = self->size + start;
	if (end < 0)
		end = self->size + end;
	if (start > end && end >= 0)
		end = end + 1 - range[3];
	else if (start < end && end <= upper)
		upper = end - 1 + range[3];
	handle_error(self, start, end);
	list = lst(arena, 0);
	while (start >= end && start <= upper)
		append(&list, (t_obj *)self->members[apply_step(&start, step)], arena);
	return (list);
}

t_obj	*pop(t_list *self, int index)
{
	t_obj	*res;

	if (self->size < 1)
		return (NULL);
	if (index < 0)
		index = (int)self->size + index;
	if (index >= (int)self->size || self->size == 0 || index < 0)
		return (display_error("Out_of_Range index: ", &index, 10), NULL);
	res = self->members[index];
	memmove(&self->members[index], &self->members[index + 1],
		(self->size - 1 - index) * sizeof(t_obj));
	self->size--;
	return (res);
}

void	append(t_list **self, t_obj *data, t_arena *arena)
{
	if (!(*self))
		return ;
	if ((*self)->size >= (*self)->cap)
		*self = realloc_list(*self, arena);
	(*self)->members[(*self)->size++] = data;
}
